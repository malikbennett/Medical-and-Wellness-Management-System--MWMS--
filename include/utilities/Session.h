#pragma once
#include <User.h>

// Handles Active Session ; stores and manage the state of the currently logged-in user
class Session
{
public:
    // Return the current active user in session
    static User* GetCurrentUser();
    // Logs in the respective user in session
    static unsigned int Login(string& username, string& password);
    // Logs user out of the current session
    static void Logout();
private:
    // Current user active in the session
    static User* currentUser;
};
