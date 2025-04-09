#pragma once
#include "User.h"
#include "Role.h"

// Handles Active Session
class Session {
public:
    // Return the current active user in session
    static User* GetCurrentUser();
    // Logs in the respective user in session
    static void StartSession(int userId, const string& username, const string& password, Role role);
    // Logs user out of the current session
    static void Logout();
    // Validates user input before authentication
    static bool ValidateCredentials(const string &username, const string &password, const string &role);
    // Authenticate User entered data
    static unsigned int AuthenticateUser(const string &username, const string &password, const string &role);
    // Gets the role data from the role database
    static Role LoadRoleFromFile(const string& filePath, int roleNumber);

private:
    // Current user active in the session
    static User* currentUser;
    // File path to the user information database
    static string userInfoPath;
    // File path to the role information database
    static string userRolePath;
};
