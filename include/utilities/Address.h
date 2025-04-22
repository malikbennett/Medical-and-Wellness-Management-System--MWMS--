#pragma once

#include <string>
#include <sstream>
#include <fstream>

using namespace std;

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
