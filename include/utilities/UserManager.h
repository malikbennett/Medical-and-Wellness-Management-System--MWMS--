#pragma once

#include <string>
#include <Patient.h>
#include <vector>

using namespace std;
// User Profile Base Class
struct IUserProfile
{
    virtual ~IUserProfile() {}
};
// Employee Temp
struct EmployeeProfile : public IUserProfile
{
    vector<string> records;
    EmployeeProfile(vector<string> records){
        this->records = records;
    }
};
// Patient Temp
struct PatientProfile : public IUserProfile
{
    vector<string> records;
    PatientProfile(vector<string> records){
        this->records = records;
    };
};
// DataType to store UserData/Record; avoids search for same user over and over
struct UserDataBuffer
{
    int userNumber;
    string username;
    string encryptedPassword;
    int roleId;
    bool isLocked;
    int attemptsRemainding;
    // Constructor
    UserDataBuffer(int userNumber, string username, string encryptedPassword, int roleId, bool isLocked, int attemptsRemainding)
        : userNumber(userNumber), username(username), encryptedPassword(encryptedPassword), roleId(roleId),
        isLocked(isLocked), attemptsRemainding(attemptsRemainding) {};
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
    // Finds PatientInfo
    static IUserProfile *getProfileInfo(int roleNumber, int userNumber);

    static vector<UserDataBuffer*> getAllUsers();
    static vector<IUserProfile*> getAllUserProfile();
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
