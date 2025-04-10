#include <UserManager.h>
#include <Session.h>
#include <fstream>

User *Session::currentUser = nullptr;

User *Session::GetCurrentUser()
{
    // Returns currentUser
    return currentUser;
}

unsigned int Session::Login(const string &username, const string &password)
{
    // Delete previous session if exist
    if (currentUser){
        delete currentUser;
    }
    int userNumber;
    string uname = username;
    string passwrd = password;
    Role role;
    // Authenticate User
    UserManager::AuthenticateUser(userNumber, uname, passwrd, role);
    // Create and Sets the currentUser into session
    currentUser = new User(userNumber, uname, passwrd, role);
    if(!currentUser)
        return 1;
    return 0;
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
