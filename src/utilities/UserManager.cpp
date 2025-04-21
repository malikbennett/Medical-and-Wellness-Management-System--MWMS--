#include <UserManager.h>
#include <Constants.h>
#include <Helper.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <wx/wx.h>
#include <User.h>

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
            if (data.getRole().roleLevel == "PATIENT") // Patient
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
    // Vectoe to store fields
    vector<string> fields;
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
            // Clear fields after each iteration
            fields.clear();
            // Variable to store each field
            string token;
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
    return fields;
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
        string header;
        getline(file, header); // Skip header
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

void UserManager::decrementAttempts(User &userData)
{
    if (userData.getAttemptsRemaining() == 1)
    {
        if (!userData.locked())
            userData.toggleLock();
    }
    else
    {
        int rem = userData.getAttemptsRemaining();
        rem--;
        userData.setAttemptsRemaining(rem);
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
        const int userFieldWidths[6] = {USER_NUMBER_LENGTH, USERNAME_LENGTH, PASSWORD_LENGTH, ROLE_NUMBER_LENGTH, ATTEMPTS_REMAINING_LENGTH, ACCOUNT_LOCKED_LENGTH};
        int colSize = getFileFields(userInfoPath).size();
        // total line size + colSize(to account for ',')
        int userTotalWidth = colSize;
        for (auto &field : userFieldWidths)
        {
            userTotalWidth += field;
        }
        // Open User info File
        fstream file(userInfoPath, ios::in | ios::out | ios::binary);
        if (!file.is_open())
        {
            // Returns an error is file did not open successfully
            throw runtime_error("User File Information Could not open");
        }
        string header;
        getline(file, header); // Skip header
        // Variable to store record
        string line;
        streampos start = file.tellg();
        int lineNum = 0;
        bool found = false;
        // Find User we need to save in file
        while (getline(file, line))
        {
            // Compare the first n amount (i.e USER_NUMBER) of char
            if (stoi(line.substr(0, userFieldWidths[0])) == userData.getUserNumber())
            {
                found = true;
                break;
            }
            ++lineNum;
        }
        stringstream ss;
        ss << padString(to_string(userData.getUserNumber()), userFieldWidths[0])
           << ',' << padString(userData.getUsername(), userFieldWidths[1])
           << ',' << padString(userData.getPassword(), userFieldWidths[2])
           << ',' << padString(to_string(userData.getRole().roleNumber), userFieldWidths[3])
           << ',' << padString(to_string(userData.getAttemptsRemaining()), userFieldWidths[4])
           << ',' << padString((userData.locked()) ? "1" : "0", userFieldWidths[5])
           << ',';
        string record = ss.str();
        if (record.length() != userTotalWidth)
        {
            cerr << "Record length mismatch. Record is " << record.length() << ", expected " << userTotalWidth << endl;
            file.close();
            return;
        }
        if (found)
        {
            int recordSize = userTotalWidth + 1;
            file.seekp(start + static_cast<streamoff>(lineNum * recordSize), ios::beg);
            file << record << '\n';
        }
        file.close();
        if(!userData.getProfileRecords().empty()){
            // Saving Profile Records
            vector<int> profileFieldWidths;
            int profileTotalWidth;
            int profileColSize;
            stringstream profileSS;
            string profileRecord;
            if (userData.getRole().roleLevel == "PATIENT")
            {
                // width of each field
                profileFieldWidths = {
                    USER_NUMBER_LENGTH, USER_NUMBER_LENGTH, NAME_LENGTH, NAME_LENGTH, NAME_LENGTH,
                    TRN_LENGTH, DATE_LENGTH, DATE_LENGTH, GENDER_LENGTH, MARTIAL_STATUS_LENGTH, NOK_LENGTH,
                    PHONE_NUMBER_LENGTH, MEDICAL_HISTORY_LENGTH, EMAIL_ADDRESS_LENGTH, PHONE_NUMBER_LENGTH, ADDRESS_LENGTH};
                profileColSize = getFileFields(patientInfoPath).size();
                // total line size + colSize(to account for ',')
                profileTotalWidth = profileColSize;
                for (auto &field : profileFieldWidths)
                {
                    profileTotalWidth += field;
                }
                file.open(patientInfoPath, ios::in | ios::out | ios::binary);
                if (!file.is_open())
                {
                    // Returns an error is file did not open successfully
                    throw runtime_error("User File Information Could not open");
                }
                getline(file, header); // Skip header
                while (getline(file, line))
                {
                    // Compare the first n amount (i.e USER_NUMBER) of char
                    if (stoi(line.substr(0, profileFieldWidths[0])) == userData.getProfileRecords()[0])
                    {
                        found = true;
                        break;
                    }
                    ++lineNum;
                }
                profileSS << padString(userData.getProfileRecords()[0], profileFieldWidths[0])
                          << ',' << padString(userData.getProfileRecords()[1], profileFieldWidths[1])
                          << ',' << padString(userData.getProfileRecords()[2], profileFieldWidths[2])
                          << ',' << padString(userData.getProfileRecords()[3], profileFieldWidths[3])
                          << ',' << padString(userData.getProfileRecords()[4], profileFieldWidths[4])
                          << ',' << padString(userData.getProfileRecords()[5], profileFieldWidths[5])
                          << ',' << padString(userData.getProfileRecords()[6], profileFieldWidths[6])
                          << ',' << padString(userData.getProfileRecords()[7], profileFieldWidths[7])
                          << ',' << padString(userData.getProfileRecords()[8], profileFieldWidths[8])
                          << ',' << padString(userData.getProfileRecords()[9], profileFieldWidths[9])
                          << ',' << padString(userData.getProfileRecords()[10], profileFieldWidths[10])
                          << ',' << padString(userData.getProfileRecords()[11], profileFieldWidths[11])
                          << ',' << padString(userData.getProfileRecords()[12], profileFieldWidths[12])
                          << ',' << padString(userData.getProfileRecords()[13], profileFieldWidths[13])
                          << ',' << padString(userData.getProfileRecords()[14], profileFieldWidths[14])
                          << ',' << padString(userData.getProfileRecords()[15], profileFieldWidths[15])
                          << ',';
                profileRecord = profileSS.str();
            }
            else
            {
                profileFieldWidths = {
                    USER_NUMBER_LENGTH, USER_NUMBER_LENGTH, NAME_LENGTH, NAME_LENGTH, NAME_LENGTH,
                    DATE_LENGTH, DATE_LENGTH, DEPARTMENT_LENGTH, GENDER_LENGTH,
                    TRN_LENGTH, JOB_TITLE_LENGTH, NAME_LENGTH
                };
                profileColSize = getFileFields(employeeInfoPath).size();
                profileTotalWidth = profileColSize;
                for (auto &field : profileFieldWidths)
                {
                    profileTotalWidth += field;
                }
                file.open(employeeInfoPath, ios::in | ios::out | ios::binary);
                if (!file.is_open())
                {
                    // Returns an error is file did not open successfully
                    throw runtime_error("User File Information Could not open");
                }
                getline(file, header); // Skip header
                while (getline(file, line))
                {
                    // Compare the first n amount (i.e USER_NUMBER) of char
                    if (stoi(line.substr(0, profileFieldWidths[0])) == userData.getProfileRecords()[0])
                    {
                        found = true;
                        break;
                    }
                    ++lineNum;
                }
                profileSS << padString(userData.getProfileRecords()[0], profileFieldWidths[0])
                          << ',' << padString(userData.getProfileRecords()[1], profileFieldWidths[1])
                          << ',' << padString(userData.getProfileRecords()[2], profileFieldWidths[2])
                          << ',' << padString(userData.getProfileRecords()[3], profileFieldWidths[3])
                          << ',' << padString(userData.getProfileRecords()[4], profileFieldWidths[4])
                          << ',' << padString(userData.getProfileRecords()[5], profileFieldWidths[5])
                          << ',' << padString(userData.getProfileRecords()[6], profileFieldWidths[6])
                          << ',' << padString(userData.getProfileRecords()[7], profileFieldWidths[7])
                          << ',' << padString(userData.getProfileRecords()[8], profileFieldWidths[8])
                          << ',' << padString(userData.getProfileRecords()[9], profileFieldWidths[9])
                          << ',' << padString(userData.getProfileRecords()[10], profileFieldWidths[10])
                          << ',' << padString(userData.getProfileRecords()[11], profileFieldWidths[11])
                          << ',';
                profileRecord = profileSS.str();
            }
            if (profileRecord.length() != profileTotalWidth)
            {
                cerr << "Record length mismatch. Record is " << profileRecord.length() << ", expected " << profileTotalWidth << endl;
                file.close();
                return;
            }
            if (found)
            {
                // Go to correct offset (start + lineNum * recordSize)
                int recordSize = profileTotalWidth + 1; // +1 for newline
                file.seekp(start + static_cast<streamoff>(lineNum * recordSize), ios::beg);
                file << profileRecord << '\n'; // overwrite
            }
            file.close();
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
