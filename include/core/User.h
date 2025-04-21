// User class definition
#pragma once

#include <Role.h>
#include <string>
#include <vector>

using namespace std;

// Base User Class
class User
{
public:
    // User constructor
    User(int userNumber, const string &username, const string &password, Role role);
    User(vector<string> UserData);
    User(User &data);
    virtual ~User() = default;
    // prints user details
    void show() const;
    // Setters
    void setProfileRecords(vector<string> ProfileRecords);
    void setAttemptsRemaining(int i);
    void toggleLock(int i = -1);
    void setRole(Role role);
    // Getters
    // returns the user's userID
    const int getUserNumber() const;
    // returns the user's username
    const string getUsername() const;
    // returns the user's password
    const string getPassword() const;
    // check if user account is locked
    const bool locked() const;
    // returns the user's remaining attempts
    const int getAttemptsRemaining() const;
    // returns the user's Role
    const vector<string> &getProfileRecords() const;
    const Role &getRole() const;

private:
    // unique userId
    int userNumber;
    // user's username
    string username;
    // user's password
    string password;
    // user's Role
    Role jobRole;
    // if iser account it locked
    bool isLocked;
    // number of attempts user has remainding
    int attemptsRemaining;
    // profileRecords
    vector<string> ProfileRecords;
    // sets the user number with a limit of 5 digits
    void setUserNumber(int num);
};
