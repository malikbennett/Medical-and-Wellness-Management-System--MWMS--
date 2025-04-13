#pragma once

#include <string>

using namespace std;
// DataType to store UserData/Record; avoids search for same user over and over
struct UserData
{
    int userNumber;
    string username;
    string encryptedPassword;
    int roleId;
    bool isLocked;
    int attemptsRemainding;
    // Constructor
    UserData(int userNumber,string username,string encryptedPassword,int roleId,bool isLocked,int attemptsRemainding){
        this->userNumber = userNumber;
        this->username = username;
        this->encryptedPassword = encryptedPassword;
        this->roleId = roleId;
        this->isLocked = isLocked;
        this->attemptsRemainding = attemptsRemainding;
    };
};

// fills with spaces to match field width
string padString(const string &value, int width);

// UserManager class responsible for validating credentials, managing failed login attempts, locking/unlocking accounts, and other user-related logic.
class UserManager
{
public:
    // Finds User By Username
    static void *FindUserByUsername(const string &username);
    // Increments failed login attempts
    static void decrementAttempts(UserData &userData);
    // reset failed login attempts
    static void resetAttempts(UserData &userData);
    // Validates user input before authentication
    static bool ValidateCredentials(const string &username, const string &password);
    // Locks an account after too many failed attempts
    static void lockAccount(UserData &userData);
    // Unlocks an account (admin-only)
    static void unlockAccount(UserData &userData);
    // saves user data
    static void saveUserData(const UserData &userData = *UserManager::data);

    // returns userData
    static UserData* getData();

private:
    // File path to the user information database
    static string userInfoPath;
    // UserData
    static UserData* data;
};
