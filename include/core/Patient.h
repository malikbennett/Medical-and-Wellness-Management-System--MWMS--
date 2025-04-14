#pragma once

#include <User.h>

// PhoneNumber class
class Phone
{
private:
    int areaCode;
    int exchange;
    int lineNumber;
};
// Address Class
class Address
{
private:
    int streetNumber;
    string streetName;
    string parish;
    string country;
};
// Patient Class
class Patient : public User{
public:

private:
    int patientNumber;
    string patientName;
    string patientGender;
    Date patientDOB;
    Phone phoneNumber;
    Address patientAddress;
};
