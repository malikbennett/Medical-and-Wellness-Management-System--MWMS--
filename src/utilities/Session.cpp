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
        // Delete previous session if exist
        if (currentUser)
        {
            delete currentUser;
            currentUser = nullptr;
        }
        // Validate user input
        if (!UserManager::ValidateCredentials(username, password))
            return 1;
        // Pad variable for comparison
        username = padString(username, USERNAME_LENGTH);
        // Load user data from file
        vector<string> userInfo = UserManager::FindUserByUsername(username);
        if(userInfo.empty())
            throw runtime_error("Username not found.");
        unAuthUser = new User(userInfo);
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

unsigned int Session::Signup(vector<string> profile)
{
    try
    {
        // Delete previous session if exist
        if (currentUser)
        {
            delete currentUser;
            currentUser = nullptr;
        }
        // Validate user input
        if (!UserManager::ValidateCredentials(profile))
            return 1;
        // Pad variables
        profile[0] = padString(profile[0], USERNAME_LENGTH);
        int userNumber = UserManager::getNewUserNumber();
        int patientNumber = UserManager::getNewPatientNumber();
        std::cout << userNumber << std::endl;
        // Variable to store encryption key
        string key;
        // Get key from file
        Encrypt::getInstance().readKeyFromFile("../../data/encryption.key", key);
        // Encrypts the password the user gave us to we can check it against the one we have in our database
        profile[1] = Encrypt::getInstance().xorEncryptDecrypt(profile[1], key);
        profile[1] = padString(profile[1], PASSWORD_LENGTH);
        Role role = Role::LoadRoleFromFile(Role::userRolePath, 7);
        unAuthUser = new User(userNumber, profile[0], profile[1], role);
        vector<string> profileRecord = {
            to_string(userNumber),
            to_string(patientNumber),
            profile[2],
            profile[3],
            profile[4],
            profile[5],
            profile[6],
            profile[7],
            profile[8],
            profile[9],
            profile[10],
            profile[11],
            profile[12],
            profile[13],
            profile[14],
            profile[15],
        };
        unAuthUser->setProfileRecords(profileRecord);
        unAuthUser->setAttemptsRemaining(3);
        unAuthUser->toggleLock(0);
        currentUser = new Patient(*unAuthUser);
        // Error if user is not created successfully
        if (!currentUser)
            throw runtime_error("User failed to initialize");
        UserManager::saveUserData();
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
