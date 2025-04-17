// User class definition
#pragma once

#include <Role.h>
#include <string>

using namespace std;
struct UserDataBuffer;

// Base User Class
class User
{
public:
    // User constructor
    User(int userNumber, const string &username, const string &password, Role role);
    User(UserDataBuffer *data);
    virtual ~User() = default;
    // prints user details
    void show() const;
    // Getters and Setters
    // returns the user's userID
    const int getUserNumber() const;
    // returns the user's username
    const string getUserName() const;
    // returns the user's Role
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
    // sets the user number with a limit of 5 digits
    void setUserNumber(int num);
};
