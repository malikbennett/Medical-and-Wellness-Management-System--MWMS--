#include <UserManager.h>
#include <Employee.h>
#include <Patient.h>
#include <Encryption.h>
#include <Constants.h>
#include <Helper.h>
#include <Session.h>
#include <fstream>
#include <wx/wx.h>

User *Session::currentUser = nullptr;
User *Session::unAuthUser = nullptr;

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
        username = padString(username, USERNAME_LENGTH);
        // Load user data from file
        vector<string> userInfo = UserManager::FindUserByUsername(username);
        unAuthUser =  new User(userInfo);
        // Check if account is locked
        if (unAuthUser->locked())
            throw runtime_error("Unable to sign in user is locked. An admin is needed");
        // Variable to store encryption key
        string key;
        // Get key from file
        Encrypt::getInstance().readKeyFromFile("../../data/encryption.key", key);
        // Encrypts the password the user gave us to we can check it against the one we have in our database
        password = Encrypt::getInstance().xorEncryptDecrypt(password, key);
        password = padString(password, PASSWORD_LENGTH);
        // checks if the passwords matches; If password does not match an Error is given
        if (password != unAuthUser->getPassword())
        {
            stringstream ss;
            ss << "Password is incorrect. You have " << unAuthUser->getAttemptsRemaining() << " attempts remaining.";
            UserManager::decrementAttempts(*unAuthUser);
            throw runtime_error(ss.str());
        }
        UserManager::LoadUserData(*unAuthUser);
        // Delete previous session if exist
        if (currentUser)
        {
            delete currentUser;
        }
        // Check if user is employee or patient and Creates them
        currentUser = (stoi(userInfo[3]) == 7) ? static_cast<User *>(new Patient(*unAuthUser)) : static_cast<User *>(new Employee(*unAuthUser));
        // Error if user is not created successfully
        if (!currentUser)
            throw runtime_error("User failed to initialize");
        delete unAuthUser;
        UserManager::resetAttempts(*currentUser);
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
