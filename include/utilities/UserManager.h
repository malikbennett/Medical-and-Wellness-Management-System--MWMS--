#pragma once

#include <string>
#include <vector>
#include <Session.h>

using namespace std;

// UserManager class responsible for validating credentials, managing failed login attempts, locking/unlocking accounts, and other user-related logic.
class UserManager
{
public:
    // Finds User By Username
    static vector<string> FindUserByUsername(const string &username                                                                                                     );
    static void LoadUserData(User &data);
    static vector<User*> getAllUsers(int roleNumber = 0);
    // Validates user input before authent                                                                                                                                                      ication
    static bool ValidateCredentials(const string &username, const string &password);
    // Increments failed login attempts
    static void decrementAttempts(User &data);
    // reset failed login attempts
    static void resetAttempts(User &data);
    // saves user data
    static void saveUserData(const User &data = *Session::GetCurrentUser());
    // File path to the user information database
    static const string userInfoPath;
    static const string patientInfoPath;
    static const string employeeInfoPath;
};
