#pragma once

#include <string>
#include <Role.h>

using namespace std;

// UserManager class responsible for validating credentials, managing failed login attempts, locking/unlocking accounts, and other user-related logic.
class UserManager{
public:
    // Authenticate User entered data
    static bool AuthenticateUser(int &userNumber,const string &username,string &password,Role &role);
    // Validates user input before authentication
    static bool ValidateCredentials(const string &username, const string &password);
    // Gets the role data from the role database
    static Role LoadRoleFromFile(const string& filePath, int roleNumber);
private:
    // Number of unsuccessful attempts
    static unsigned int attempts;
    // File path to the user information database
    static string userInfoPath;
    // File path to the role information database
    static string userRolePath;
};
