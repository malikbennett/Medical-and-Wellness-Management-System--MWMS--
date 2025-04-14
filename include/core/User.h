// User class definition
#pragma once

#include <Role.h>
#include <string>

using namespace std;

constexpr int USER_NUMBER = 5;
constexpr int USERNAME_WIDTH = 16;
constexpr int PASSWORD_WIDTH = 64;
constexpr int ROLE_NUMBER = 2;
constexpr int ATTEMPTS_REMAINDING = 1;
constexpr int ACCOUNT_LOCKED = 1;

// Date structure
struct Date{
    string day;
    string month;
    string year;
};

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
