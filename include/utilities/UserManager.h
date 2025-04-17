#pragma once

#include <string>
#include <vector>

using namespace std;

// DataType to store UserData/Record; avoids search for same user over and over
struct UserDataBuffer
{
    vector<string> UserData;
    vector<string> ProfileRecords;
    int userNumber;
    string username;
    string encryptedPassword;
    int roleId;
    bool isLocked;
    int attemptsRemainding;
    // Constructor
    // stoi(fields[0]), fields[1], fields[2], stoi(fields[3]), (lockedStr == "1"), stoi(attemptsStr)
    UserDataBuffer(vector<string> UserData);
};
// fills with spaces to match field width
string padString(const string &value, int width);
// Trims off spaces
string trimString(const string &str);
// UserManager class responsible for validating credentials, managing failed login attempts, locking/unlocking accounts, and other user-related logic.
class UserManager
{
public:
    // Finds User By Username
    static void FindUserByUsername(const string &username);
    static vector<UserDataBuffer*> getAllUsers();
    static vector<string> getFields(const string &filePath);

    // Increments failed login attempts
    static void decrementAttempts(UserDataBuffer &userData);
    // reset failed login attempts
    static void resetAttempts(UserDataBuffer &userData);
    // Validates user input before authentication
    static bool ValidateCredentials(const string &username, const string &password);
    // Locks an account after too many failed attempts
    static void lockAccount(UserDataBuffer &userData);
    // Unlocks an account (admin-only)
    static void unlockAccount(UserDataBuffer &userData);
    // saves user data
    static void saveUserData(const UserDataBuffer &userData = *UserManager::data);

    // returns userData
    static UserDataBuffer *getData();
    // File path to the user information database
    static const string userInfoPath;
    static const string patientInfoPath;
    static const string employeeInfoPath;

private:
    // UserData
    static UserDataBuffer *data;
};
