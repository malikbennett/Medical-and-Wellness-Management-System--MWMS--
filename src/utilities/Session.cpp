#include <UserManager.h>
#include <Encryption.h>
#include <Session.h>
#include <fstream>
#include <wx/wx.h>

User *Session::currentUser = nullptr;

const User *Session::GetCurrentUser()
{
    // Returns currentUser
    return currentUser;
}

unsigned int Session::Login(string &username, string &password)
{
    try
    {
        // Validate user input
        if (!UserManager::ValidateCredentials(username, password))
            return 1;
        // Pad variable for comparison
        username = padString(username,USERNAME_WIDTH);
        // Load user data from file
        UserManager::FindUserByUsername(username);
        UserData *data = UserManager::getData();
        if(!data)
            return 1;
        // Check if account is locked
        if (data->isLocked)
            throw runtime_error("Unable to sign in user is locked. An admin is needed");
        // Variable to store encryption key
        string key;
        // Get key from file
        Encrypt::getInstance().readKeyFromFile("../../data/encryption.key", key);
        // Encrypts the password the user gave us to we can check it against the one we have in our database
        password = Encrypt::getInstance().xorEncryptDecrypt(password, key);
        password = padString(password,PASSWORD_WIDTH);
        // checks if the passwords matches; If password does not match an Error is given
        if (password != data->encryptedPassword)
        {
            stringstream ss;
            ss << "Password is incorrect. You have " << data->attemptsRemainding << " attempts remaining.";
            UserManager::decrementAttempts(*data);
            throw runtime_error(ss.str());
        }
        // Delete previous session if exist
        if (currentUser)
        {
            delete currentUser;
        }
        // Creates role Object
        Role role = Role::LoadRoleFromFile(Role::userRolePath, data->roleId);
        // Create and Sets the currentUser into session
        currentUser = new User(data->userNumber, data->username, data->encryptedPassword, role);
        // Error if user is not created successfully
        if (!currentUser)
            throw runtime_error("User failed to initialize");
        UserManager::resetAttempts(*data);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        wxMessageBox(e.what(), "Login Error", wxICON_ERROR);
        return 1;
    }
    return 0;
}

void Session::Logout()
{
    // Check if there is a current user logged in
    if (currentUser)
    {
        // Saves Data before login out
        UserManager::saveUserData();
        // Delete the current user instance from memory
        delete currentUser;
        currentUser = nullptr;
        cout << "Successfully Log out" << endl;
    }
}
