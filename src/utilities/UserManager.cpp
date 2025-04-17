#include <UserManager.h>
#include <User.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <wx/wx.h>
#include <Helper.h>
#include <Constants.h>

UserDataBuffer *UserManager::data = nullptr;
const string UserManager::userInfoPath = "../../data/UserInfo.csv";
const string UserManager::patientInfoPath = "../../data/PatientInfo.csv";
const string UserManager::employeeInfoPath = "../../data/EmployeeInfo.csv";

UserDataBuffer::UserDataBuffer(vector<string> UserData): UserData(UserData),
userNumber(stoi(UserData[0])), username(UserData[1]), encryptedPassword(UserData[2]),
roleId(stoi(UserData[3])),attemptsRemainding(stoi(UserData[4])) ,isLocked((UserData[5] == "1")){};

// Gets current user and ProfileData
void UserManager::FindUserByUsername(const string &username)
{
    try
    {
        // If no userData is loaded or loaded userData is not the one requested, reload
        if (!data || data->username != username)
        {
            // save old data if loaded userData is not the one requested
            if (data)
            {
                saveUserData(*data);
                delete data;
                data = nullptr;
            }
            // Opens User Info file
            ifstream file(userInfoPath);
            if (!file.is_open())
            {
                // Returns an error is file did not open successfully
                throw runtime_error("User File Information Could not open");
            }
            // Variable to store record
            string line;
            // Skips first line
            getline(file, line);
            // Loops through each line and gets userData
            while (getline(file, line))
            {
                // Initialize a stringstream to parse record into individual fields
                istringstream ss(line);
                // Variable to store each field
                string token;
                // Vectoe to store fields
                vector<string> fields;
                // Split up and store each line into tokens
                while (getline(ss, token, ','))
                {
                    fields.push_back(token);
                }
                // Skips through each record and check if the username matches with any in our databased
                if (fields[1] != username)
                    continue;
                // Initialize UserData object
                data = new UserDataBuffer(fields);
                break;
            }
            // An Error is given if after skipping through each record username does not match any
            if (!data)
            {
                throw runtime_error("Invalid Credentials.");
            }
            // closes file
            file.close();
            // Opens Correct Database
            if (data->roleId == 7)
                file.open(patientInfoPath);
            else
                file.open(employeeInfoPath);
            // Checks if file open correctly
            if (!file.is_open())
                throw runtime_error("File failed to open");
            // Skip first line
            getline(file, line);
            // Loops through each line and gets userProfileInfo
            while (getline(file, line))
            {
                istringstream ss(line);
                vector<string> fields;
                string token;
                while (getline(ss, token, ','))
                    fields.push_back(token);
                if (fields.size() < 16 && data->roleId == 7)
                    continue;
                if (fields.size() < 12 && data->roleId != 7)
                    continue;
                if (stoi(fields.at(0)) != data->userNumber)
                    continue;
                if (data->roleId == 7) // Patient
                {
                    data->ProfileRecords = fields;
                }
                else // Employee
                {
                    data->ProfileRecords = fields;
                }
            }
            file.close();
        }
    }
    catch (const std::exception &e)
    {
        cerr << "Login error: " << e.what() << endl;
        wxMessageBox(e.what(), "Login Error", wxICON_ERROR);
    }
}
// Gets all users and Profile Data
vector<UserDataBuffer *> UserManager::getAllUsers()
{
    try
    {
        vector<UserDataBuffer *> users;
        ifstream file(userInfoPath);
        if (!file.is_open())
            throw runtime_error("User File Information Could not open");
        string line;
        getline(file, line); // Skip header
        while (getline(file, line))
        {
            istringstream ss(line);
            string token;
            vector<string> fields;
            while (getline(ss, token, ','))
                fields.push_back(token);
            UserDataBuffer *user = new UserDataBuffer(fields);
            string profilePath = (user->roleId == 7) ? patientInfoPath : employeeInfoPath;
            ifstream profileFile(profilePath);
            if (!profileFile.is_open())
                throw runtime_error("Profile file failed to open");
            string profileLine;
            getline(profileFile, profileLine); // Skip header
            while (getline(profileFile, profileLine))
            {
                istringstream profileSS(profileLine);
                string profileToken;
                vector<string> profileFields;
                while (getline(profileSS, profileToken, ','))
                    profileFields.push_back(profileToken);
                if (user->roleId == 7 && profileFields.size() < 16)
                    continue;
                if (user->roleId != 7 && profileFields.size() < 12)
                    continue;
                if (stoi(profileFields[0]) != user->userNumber)
                    continue;
                user->ProfileRecords = profileFields;
                break;
            }
            profileFile.close();
            users.push_back(user);
        }
        file.close();
        return users;
    }
    catch (const exception &e)
    {
        cerr << "Error in getAllUsers: " << e.what() << endl;
        return {};
    }
}

vector<string> UserManager::getFields(const string &filePath)
{
    vector<string> fields;
    try
    {
        ifstream file;
        file.open(filePath);
        if (file.fail())
        {
            throw runtime_error("File fail to open");
        }
        string line;
        getline(file, line);
        istringstream ss(line);
        string token;
        while (getline(ss, token, ','))
        {
            fields.push_back(token);
        }
        if (fields.empty())
        {
            throw runtime_error("Error retrieving fields");
        }
        return fields;
    }
    catch (exception e)
    {
        cerr << e.what() << endl;
    }
    return fields;
};

bool UserManager::ValidateCredentials(const string &username, const string &password)
{
    try
    {
        // Checks if user input is empty
        if (username.empty() || password.empty())
        {
            throw runtime_error("Input cannot be empty");
        }
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        wxMessageBox(e.what(), "Login Error", wxICON_ERROR);
        return false;
    }
    return false;
}

void UserManager::decrementAttempts(UserDataBuffer &userData)
{
    if (userData.attemptsRemainding == 1)
    {
        lockAccount(userData);
    }
    else
    {
        userData.attemptsRemainding--;
    }
};

void UserManager::resetAttempts(UserDataBuffer &userData)
{
    userData.attemptsRemainding = 3;
};

void UserManager::lockAccount(UserDataBuffer &userData)
{
    userData.isLocked = 1;
};

void UserManager::unlockAccount(UserDataBuffer &userData)
{
    userData.isLocked = 0;
};

void UserManager::saveUserData(const UserDataBuffer &userData)
{
    try
    {
        // width of each field
        const int fieldWidths[6] = {USER_NUMBER_LENGTH, USERNAME_LENGTH, PASSWORD_LENGTH, ROLE_NUMBER_LENGTH, ATTEMPTS_REMAINING_LENGTH, ACCOUNT_LOCKED_LENGTH};
        int colSize = getFields(userInfoPath).size();
        // total line size + colSize(to account for ',')
        const int totalWidth = USER_NUMBER_LENGTH + USERNAME_LENGTH + PASSWORD_LENGTH + ROLE_NUMBER_LENGTH + ATTEMPTS_REMAINING_LENGTH + ACCOUNT_LOCKED_LENGTH + colSize;
        // Open User info File
        fstream file(userInfoPath, ios::in | ios::out);
        if (!file.is_open())
        {
            // Returns an error is file did not open successfully
            throw runtime_error("User File Information Could not open");
        }
        // Variable to store record
        string line;
        int lineNum = 0;
        // Find User we need to save in file
        while (getline(file, line))
        {
            // Compare the first n amount (i.e USER_NUMBER) of char
            if (stoi(line.substr(0, fieldWidths[0])) == userData.userNumber)
            {
                break;
            }
            ++lineNum;
        }
        stringstream ss;
        ss << padString(to_string(userData.userNumber), USER_NUMBER_LENGTH)
           << ',' << userData.username
           << ',' << userData.encryptedPassword
           << ',' << padString(to_string(userData.roleId), ROLE_NUMBER_LENGTH)
           << ',' << padString(to_string(userData.attemptsRemainding), ATTEMPTS_REMAINING_LENGTH)
           << ',' << padString((userData.isLocked) ? "1" : "0", ACCOUNT_LOCKED_LENGTH);
        // Calculate byte offset
        int offset = lineNum * (totalWidth + 1); // +1 for newline
        // Seek to position and overwrite
        file.seekp(offset, ios::beg);
        file << ss.str();
        file.close();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

UserDataBuffer *UserManager::getData()
{
    return data;
};
