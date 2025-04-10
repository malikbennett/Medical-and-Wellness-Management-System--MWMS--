#include <UserManager.h>
#include <Encryption.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <wx/wx.h>
#include <vector>

string UserManager::userInfoPath = "../../data/UserInfo.csv";
string UserManager::userRolePath = "../../data/UserRoles.csv";

bool UserManager::AuthenticateUser(int &userNumber,const string &username,string &password,Role &role)
{
    try
    {
        // Validate Credential before authenticating
        if (!ValidateCredentials(username, password))
        {
            return 1;
        }
        // Opens User Info file
        ifstream file(userInfoPath);
        if (!file.is_open())
        {
            // Returns an error is file did not open successfully
            throw runtime_error("Failed to open User Info Data");
        }
        // Variable to store record
        string line;
        // Skips the first line
        getline(file, line);
        // Encryption Key
        string key;
        Encrypt::getInstance().readKeyFromFile("../../data/encryption.key", key);
        // Loops through each line; starting from the second record
        while (getline(file, line))
        {
            // Initialize a stringstream to parse record into individual fields
            stringstream ss(line);
            // Variable to store each field's value
            string token;
            // Vector which stores each token for later access
            vector<string> fields;
            // Loops through the stringstream and store each value seperated by a "," into token variable
            while (getline(ss, token, ','))
            {
                // Adds value into field variable
                fields.push_back(token);
            }
            // If the field size(amount of columns) does not match 4; that means there is an error with that record and it should be skipped
            if (fields.size() != 6)
                continue;
            // Variable for username from our database
            string fileUsername = fields[1];
            // Variable for password from our database
            string filePassword = fields[2];
            // Variable for roleNumber from our database
            int fileRoleId = stoi(fields[3]);
            // Skips through each record and check if the username matches with any in our databased
            if (fileUsername != username)
                continue;
            // Encrypts the password the user gave us to we can check it against the one we have in our database
            password = Encrypt::getInstance().xorEncryptDecrypt(password, key);
            // If the username matches we now check if the password matches as well
            if (password != filePassword)
            {
                // If password does not match an Error is given
                throw runtime_error("Password is incorrect.");
            }
            // Creates role Object
            role = LoadRoleFromFile(userRolePath, fileRoleId);
            // Sets user number
            userNumber = stoi(fields[0]);
            return 0;
        }
        // An Error is given if after skipping through each record username does not match any
        throw runtime_error("Username not found.");
    }
    catch (const exception &e)
    {
        cerr << "Login error: " << e.what() << endl;
        wxMessageBox(e.what(), "Login Error", wxICON_ERROR);
        return 1;
        ;
    }
    wxMessageBox("Unknown Error", "Unknown", wxICON_ERROR);
    return 1;
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

Role UserManager::LoadRoleFromFile(const string &filePath, int roleNumber)
{
    try
    {
        // Open role data file
        ifstream file(filePath);
        // Checks if the file failed to open
        if (file.fail())
        {
            // If file failed an error is thrown
            wxMessageBox("Role data file failed to open", "File Error", wxICON_ERROR);
            throw runtime_error("Role data file failed to open");
        }
        // Variable to store record
        string line;
        // Skips to first line
        getline(file, line);
        // Loops through each store
        while (getline(file, line))
        {
            // Initialize a stringstream to parse record into individual fields
            stringstream ss(line);
            // Variable to store each field's value
            string token;
            // Vector which stores each token for later access
            vector<string> fields;
            // Loops through the stringstream and store each value seperated by a "," into token variable
            while (getline(ss, token, ','))
            {
                // Adds value into field variable
                fields.push_back(token);
            }
            // If the field size(amount of columns) does not match 3; that means there is an error with that record and it should be skipped
            if (fields.size() != 3)
                continue;
            // convert roleNumber from database into an int and stores it
            int roleID = stoi(fields[0]);
            // Checks if roleNumbers match
            if (roleID == roleNumber)
            {
                // Closes file
                file.close();
                // Returns an instance of type Role
                return Role(roleID, fields[1], fields[2]);
            }
        }
        // Closes file
        file.close();
    }
    catch (const exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    // Returns empty Role if role was not created successfully
    return Role();
}
