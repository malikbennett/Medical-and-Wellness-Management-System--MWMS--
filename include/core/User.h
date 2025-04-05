// User class definition
#pragma once

#include <Role.h>
#include <string>

using namespace std;

// Base User Class
class User
{
public:
    // User constructor
    User(int userNumber, const string &username,const string& password, Role role);
     // returns the user's userID
    int getUserNumber() const;
     // prints user details
    void show();

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
