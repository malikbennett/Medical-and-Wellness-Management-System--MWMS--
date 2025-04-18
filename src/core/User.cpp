// User class implementation
#include <UserManager.h>
#include <User.h>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <string>
#include <Helper.h>

User::User(int userNumber, const string &username,const string& password, Role role)
    : jobRole(role), username(username), password(password)
{
    setUserNumber(userNumber);
}

User::User(vector<string> UserData): userNumber(stoi(UserData[0])), username(UserData[1]),
password(UserData[2]), attemptsRemaining(stoi(UserData[4])) ,isLocked((UserData[5] == "1")){
    this->jobRole = Role::LoadRoleFromFile(Role::userRolePath, stoi(UserData[3]));
};

User::User(User &data)
{
    setUserNumber(data.getUserNumber());
    this->username = trimString(data.getUsername());
    this->password = trimString(data.getPassword());
    this->attemptsRemaining = data.getAttemptsRemaining();
    this->isLocked = data.locked();
    this->jobRole = Role::LoadRoleFromFile(Role::userRolePath, data.getRole().roleNumber);
}

void User::setProfileRecords(vector<string> ProfileRecords){this->ProfileRecords = ProfileRecords;}
void User::setAttemptsRemaining(int i) { this->attemptsRemaining = 1; };
void User::toggleLock(){this->isLocked = !this->isLocked;}
const int User::getUserNumber() const {return this->userNumber;}
const string User::getUsername() const {return this->username;}
const string User::getPassword() const {return this->password;}
const bool User::locked() const {return this->isLocked;}
const int User::getAttemptsRemaining() const {return this->attemptsRemaining;}
const vector<string> &User::getProfileRecords() const {return this->ProfileRecords;}
const Role& User::getRole() const {return this->jobRole;}

void User::setUserNumber(int userNumber)
{
    try
    {
        if (userNumber >= 0 && userNumber <= 99999)
        {
            this->userNumber = userNumber;
        }
        else
        {
            throw runtime_error("User number must be 5 digits or less");
        }
    }
    catch (const exception &e)
    {
        cerr << e.what() << '\n';
    }
}

void User::show() const{
    cout << this->username << "\n"
         << this->password << "\n"
         << this->getUserNumber() << endl;
}
