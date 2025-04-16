#include <UserManager.h>
#include <User.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <wx/wx.h>

UserDataBuffer *UserManager::data = nullptr;
const string UserManager::userInfoPath = "../../data/UserInfo.csv";
const string UserManager::patientInfoPath = "../../data/PatientInfo.csv";
const string UserManager::employeeInfoPath = "../../data/EmployeeInfo.csv";

string padString(const string &value, int width)
{
    string padded = value;
    padded.resize(width, ' ');
    return padded;
}
string trimString(const string &str)
{
    size_t first = str.find_first_not_of(' ');
    if (first == string::npos)
        return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

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
            // Loops through each line
            while (getline(file, line))
            {
                // Initialize a stringstream to parse record into individual fields
                istringstream ss(line);
                // Initialize Different variables to store fields
                string fileUserNumber, fileUsername, filePassword, fileRoleIdStr, attemptsStr, lockedStr;
                // Store each field in its respected variable
                getline(ss, fileUserNumber, ',');
                getline(ss, fileUsername, ',');
                getline(ss, filePassword, ',');
                getline(ss, fileRoleIdStr, ',');
                getline(ss, attemptsStr, ',');
                getline(ss, lockedStr, ',');
                // Skips through each record and check if the username matches with any in our databased
                if (fileUsername != username)
                    continue;
                // Initialize UserData object
                data = new UserDataBuffer(stoi(fileUserNumber), fileUsername, filePassword, stoi(fileRoleIdStr), (lockedStr == "1"), stoi(attemptsStr));
                break;
            }
            // An Error is given if after skipping through each record username does not match any
            if (!data)
            {
                throw runtime_error("Invalid Credentials.");
            }
            // closes file
            file.close();
        }
    }
    catch (const std::exception &e)
    {
        cerr << "Login error: " << e.what() << endl;
        wxMessageBox(e.what(), "Login Error", wxICON_ERROR);
    }
}

IUserProfile* UserManager::getProfileInfo(int roleNumber, int userNumber)
{
    try
    {
        // Initialize file
        ifstream file;
        // Open Correct Database
        if (roleNumber == 7)
            file.open(patientInfoPath);
        else
            file.open(employeeInfoPath);
        // Checks if file open correctly
        if (!file.is_open())
            throw runtime_error("File failed to open");
        // Skip first line
        string headerLine;
        getline(file, headerLine);
        string line;
        while (getline(file, line))
        {
            istringstream ss(line);
            vector<string> fields;
            string token;
            while (getline(ss, token, ','))
                fields.push_back(token);
            if (fields.size() < 16 && roleNumber == 7) continue;
            if (fields.size() < 12 && roleNumber != 7) continue;
            if (stoi(fields.at(0)) != userNumber) continue;
            IUserProfile *profile = nullptr;
            if (roleNumber == 7) // Patient
            {
                profile = new PatientProfile(fields);
            }
            else // Employee
            {
                profile = new EmployeeProfile(fields);
            }
            file.close();
            return profile;
        }

        file.close();
        return nullptr; // No matching record found
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error in getProfileInfo: " << e.what() << '\n';
        return nullptr;
    }
}

vector<UserDataBuffer*> UserManager::getAllUsers(){
    try{
        ifstream file;
        file.open(userInfoPath);
        if(file.fail()){
            throw runtime_error("File fail to open");
        }
        vector<UserDataBuffer *> users;
        string line;
        getline(file, line);
        while (getline(file, line))
        {
            istringstream ss(line);
            string token;
            vector<string> fields;
            while (getline(ss,token,','))
            {
                fields.push_back(token);
            }
            if(fields.size() < 6) continue;
            UserDataBuffer *user = new UserDataBuffer(stoi(fields.at(0)), fields.at(1),fields.at(2),stoi(fields.at(3)),(fields.at(5) == "1"),stoi(fields.at(4)));
            users.push_back(user);
        }
        return users;
    }
    catch (exception e)
    {
        cerr << e.what() << endl;
    }
};

vector<string> UserManager::getFields(const string &filePath){
        try{
        ifstream file;
        file.open(filePath);
        if(file.fail()){
            throw runtime_error("File fail to open");
        }
        string line;
        getline(file, line);
        istringstream ss(line);
        string token;
        vector<string> fields;
        while (getline(ss,token,','))
        {
            fields.push_back(token);
        }
        if(fields.empty()){
            throw runtime_error("Error retrieving fields");
        }
        return fields;
        }
        catch (exception e)
        {
            cerr << e.what() << endl;
        }
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

void UserManager::unlockAccount(UserDataBuffer &userData) {};

void UserManager::saveUserData(const UserDataBuffer &userData)
{
    try
    {
        // width of each field
        const int fieldWidths[6] = {USER_NUMBER, USERNAME_WIDTH, PASSWORD_WIDTH, ROLE_NUMBER, ATTEMPTS_REMAINDING, ACCOUNT_LOCKED};
        // total line size + 5 for commas
        const int totalWidth = USER_NUMBER + USERNAME_WIDTH + PASSWORD_WIDTH + ROLE_NUMBER + ATTEMPTS_REMAINDING + ACCOUNT_LOCKED + 5;
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
        ss << padString(to_string(userData.userNumber), USER_NUMBER)
           << ',' << userData.username
           << ',' << userData.encryptedPassword
           << ',' << padString(to_string(userData.roleId), ROLE_NUMBER)
           << ',' << padString(to_string(userData.attemptsRemainding), ATTEMPTS_REMAINDING)
           << ',' << padString((userData.isLocked) ? "1" : "0", ACCOUNT_LOCKED);
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
