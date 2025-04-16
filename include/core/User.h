// User class definition
#pragma once

#include <Role.h>
#include <string>
#include <sstream>

using namespace std;

constexpr int USER_NUMBER = 5;
constexpr int USERNAME_WIDTH = 16;
constexpr int PASSWORD_WIDTH = 64;
constexpr int ROLE_NUMBER = 2;
constexpr int ATTEMPTS_REMAINDING = 1;
constexpr int ACCOUNT_LOCKED = 1;

struct UserDataBuffer;

// PhoneNumber class
class Phone
{
public:
    Phone(int areaCode, int exchange, int lineNumber)
        : areaCode(areaCode), exchange(exchange), lineNumber(lineNumber) {};
    Phone() {};
    static Phone toPhone(const string &phone)
    {
        string areaCode, exchange, lineNumber;
        istringstream phoneStream(phone);
        getline(phoneStream, areaCode, '-');
        getline(phoneStream, exchange, '-');
        getline(phoneStream, lineNumber, '-');
        return Phone(stoi(areaCode), stoi(exchange), stoi(lineNumber));
    }

private:
    int areaCode;
    int exchange;
    int lineNumber;
};
// Address Class
class Address
{
public:
    Address(int streetNumber, string streetName, string parish, string country)
        : streetNumber(streetNumber), streetName(streetName),
          parish(parish), country(country) {};
    Address() {};
    static Address toAddress(const string &address)
    {
        string streetNumber, streetName, parish, country;
        istringstream addressStream(address);
        getline(addressStream, streetNumber, '-');
        getline(addressStream, streetName, '-');
        getline(addressStream, parish, '-');
        getline(addressStream, country, '-');
        return Address(stoi(streetNumber), streetName, parish, country);
    }

private:
    int streetNumber;
    string streetName;
    string parish;
    string country;
};
// Date structure
struct Date
{
    string day;
    string month;
    string year;
    Date(string day, string month, string year)
        : day(day), month(month), year(year) {};
    Date() {};
    static Date toDate(const string &date)
    {
        istringstream ssDate(date);
        string year, month, day;
        getline(ssDate, year, '-');
        getline(ssDate, month, '-');
        getline(ssDate, day, '-');
        return Date(day, month, year);
    }
};

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
