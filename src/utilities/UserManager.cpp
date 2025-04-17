#include <UserManager.h>
#include <User.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <wx/wx.h>
#include <Helper.h>
#include <Constants.h>

const string UserManager::userInfoPath = "../../data/UserInfo.csv";
const string UserManager::patientInfoPath = "../../data/PatientInfo.csv";
const string UserManager::employeeInfoPath = "../../data/EmployeeInfo.csv";

// Gets current user and ProfileData
void UserManager::LoadUserData(User &data)
{
    try
    {
        ifstream file;
        // Opens Correct Database
        if (data.getRole().roleNumber == 7)
            file.open(patientInfoPath);
        else
            file.open(employeeInfoPath);
        // Checks if file open correctly
        if (!file.is_open())
            throw runtime_error("File failed to open");
        string line;
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
            if (fields.size() < 16 && data.getRole().roleNumber == 7)
                continue;
            if (fields.size() < 12 && data.getRole().roleNumber != 7)
                continue;
            if (stoi(fields.at(0)) != data.getUserNumber())
                continue;
            if (data.getRole().roleNumber == 7) // Patient
            {
                data.setProfileRecords(fields);
            }
            else // Employee
            {
                data.setProfileRecords(fields);
            }
        }
        file.close();
    }
    catch (const std::exception &e)
    {
        cerr << "Login error: " << e.what() << endl;
        wxMessageBox(e.what(), "Login Error", wxICON_ERROR);
    }
}

vector<string> UserManager::FindUserByUsername(const string &username)
{
    try
    {
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
            return fields;
            break;
        }
        // closes file
        file.close();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

// Gets all users and Profile Data
vector<User *> UserManager::getAllUsers(int roleNumber)
{
    try
    {
        vector<User *> users;
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
            // sorts users by roles or if its 0 gets all users
            if (stoi(fields[3]) != roleNumber && roleNumber != 0)
                continue;
            User *user = new User(fields);
            string profilePath = (user->getRole().roleNumber == 7) ? patientInfoPath : employeeInfoPath;
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
                if (user->getRole().roleNumber == 7 && profileFields.size() < 16)
                    continue;
                if (user->getRole().roleNumber != 7 && profileFields.size() < 12)
                    continue;
                if (stoi(profileFields[0]) != user->getUserNumber())
                    continue;
                user->setProfileRecords(profileFields);
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

void UserManager::decrementAttempts(User &userData) {
    if (userData.getAttemptsRemaining() == 1)
    {
        if (!userData.locked())
            userData.toggleLock();
    }
    else
    {
        userData.setAttemptsRemaining(userData.getAttemptsRemaining() - 1);
    }
    saveUserData(userData);
};

void UserManager::resetAttempts(User &userData)
{
    userData.setAttemptsRemaining(3);
    saveUserData(userData);
};

void UserManager::saveUserData(const User &userData)
{
    try
    {
        // width of each field
        const int fieldWidths[6] = {USER_NUMBER_LENGTH, USERNAME_LENGTH, PASSWORD_LENGTH, ROLE_NUMBER_LENGTH, ATTEMPTS_REMAINING_LENGTH, ACCOUNT_LOCKED_LENGTH};
        int colSize = getFileFields(userInfoPath).size();
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
            if (stoi(line.substr(0, fieldWidths[0])) == userData.getUserNumber())
                break;
            ++lineNum;
        }
        stringstream ss;
        ss << padString(to_string(userData.getUserNumber()), USER_NUMBER_LENGTH)
           << ',' << userData.getUsername()
           << ',' << userData.getPassword()
           << ',' << padString(to_string(userData.getRole().roleNumber), ROLE_NUMBER_LENGTH)
           << ',' << padString(to_string(userData.getAttemptsRemaining()), ATTEMPTS_REMAINING_LENGTH)
           << ',' << padString((userData.locked()) ? "1" : "0", ACCOUNT_LOCKED_LENGTH);
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
