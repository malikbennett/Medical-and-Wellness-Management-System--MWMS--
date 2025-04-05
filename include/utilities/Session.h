#pragma once
#include "User.h"
#include "Role.h"
#include <vector>

class Session {
public:
    // Return the current active user in session
    static User* GetCurrentUser();
    // Logs in the respective user in session
    static void SetCurrentUser(int userId, const string& username, const string& password, Role role);
    static void Logout();
    static string Login(const string &username, const string &password, const string &role);
    static Role loadRole(const string& filePath, int roleNumber);

private:
    static User* currentUser;
    static string userInfoPath;
    static string userRolePath;
};
