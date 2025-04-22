#pragma once

#include <string>
#include <sstream>
#include <fstream>

using namespace std;

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
