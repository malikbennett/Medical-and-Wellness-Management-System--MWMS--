// User class implementation

#include <user.h>
#include <stdexcept>
#include <iostream>

User::User(int userNumber, const string &username,const string& password)
{
    setUserNumber(userNumber);
    this->username = username;
    this->password = password;
}

int User::getUserNumber() const
{
    return userNumber;
}

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

void User::show(){
    cout << this->username << "\n"
         << this->password << "\n"
         << this->userNumber << endl;
}
