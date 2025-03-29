// User class implementation

#include <user.h>
#include <stdexcept>
#include <iostream>

User::User(int userNum, string username, string password)
{
    setUserNumber(userNum);
    this->username = username;
    this->password = password;
}

int User::getUserNumber() const
{
    return userNumber;
}

void User::setUserNumber(int num)
{
    try
    {
        if (num >= 0 && num <= 99999)
        {
            this->userNumber = num;
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
