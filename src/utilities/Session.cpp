#include <Session.h>
#include <wx/wx.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <Encryption.h>

User *Session::currentUser = nullptr;
string Session::userInfoPath = "../../data/UserInfo.csv";
string Session::userRolePath = "../../data/UserRoles.csv";

User *Session::GetCurrentUser()
{
    // Returns currentUser
    return currentUser;
}

void Session::StartSession(int userId, const string &username, const string &password, Role role)
{
    // Delete previous session if exist
    if (currentUser)
        delete currentUser;
    // Create and Sets the currentUser into session
    currentUser = new User(userId, username, password, role);
}

bool Session::ValidateCredentials(const string &username, const string &password, const string &role)
{
    try
    {
        // Checks if user input is empty
        if (username.empty() || password.empty() || role.empty())
        {
            throw runtime_error("Input cannot be empty");
        }
        // Checks if role selected is a valid role in our system (even though they can only select what we give them its for safe keeping)
        if (Role::roleMap.find(role) == Role::roleMap.end())
        {
            // If role not found Error is given
            throw runtime_error("Selected role is invalid.");
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

unsigned int Session::AuthenticateUser(const string &username, const string &password, const string &role)
{
    try
    {
        // Validate Credential before authenticating
        if (!ValidateCredentials(username, password, role))
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
            if (fields.size() != 4)
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
            string encryptedInputPassword = Encrypt::getInstance().xorEncryptDecrypt(password, key);
            // If the username matches we now check if the password matches as well
            if (encryptedInputPassword != filePassword)
            {
                // If password does not match an Error is given
                throw runtime_error("Password is incorrect.");
            }
            // Checks the roleNumber of the record to the entered role against a map of Role names and Numbers
            if (fileRoleId != Role::roleMap[role])
            {
                // if roleNumber isn't found with that record then an Error is given
                throw runtime_error("User role does not match.");
            }
            // Creates role Object
            Role userRole = LoadRoleFromFile(userRolePath, fileRoleId);
            // calls setcurrentuser function to log active user in the session
            StartSession(stoi(fields[0]), fileUsername, filePassword, userRole);
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

Role Session::LoadRoleFromFile(const string &filePath, int roleNumber)
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

void Session::Logout()
{
    // Check if there is a current user logged in
    if (currentUser)
    {
        // Delete the current user instance from memory
        delete currentUser;
        currentUser = nullptr;
    }
}
