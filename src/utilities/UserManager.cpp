#include <UserManager.h>
#include <User.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <wx/wx.h>

UserData *UserManager::data = nullptr;
string UserManager::userInfoPath = "../../data/UserInfo.txt";

string padString(const string &value, int width){
    string padded = value;
    padded.resize(width, ' ');
    return padded;
}

void *UserManager::FindUserByUsername(const string &username)
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
                data = new UserData(stoi(fileUserNumber), fileUsername, filePassword, stoi(fileRoleIdStr), (lockedStr == "1"), stoi(attemptsStr));
                break;
            }
            // An Error is given if after skipping through each record username does not match any
            if (!data)
            {
                throw runtime_error("Invalid Credentials.");
            }
            //closes file
            file.close();
        }
    }
    catch (const std::exception &e)
    {
        cerr << "Login error: " << e.what() << endl;
        wxMessageBox(e.what(), "Login Error", wxICON_ERROR);
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

void UserManager::decrementAttempts(UserData &userData)
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

void UserManager::resetAttempts(UserData &userData)
{
    userData.attemptsRemainding = 3;
};

void UserManager::lockAccount(UserData &userData)
{
    userData.isLocked = 1;
};

void UserManager::unlockAccount(UserData &userData) {};

void UserManager::saveUserData(const UserData &userData)
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
        while(getline(file,line)){
            // Compare the first n amount (i.e USER_NUMBER) of char
            if(stoi(line.substr(0,fieldWidths[0])) == userData.userNumber){
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
        << ',' << padString((userData.isLocked) ? "1" : "0", ACCOUNT_LOCKED)
        ;
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

UserData *UserManager::getData()
{
    return data;
};
