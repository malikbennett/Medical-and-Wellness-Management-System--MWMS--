#pragma once

using namespace std;

#include <string>
#include <map>

struct Role{
    // unique roleID
    int roleNumber;
    // name of the role
    string roleName;
    // level of the roles permission
    string roleLevel;
    // maps role names to role numbers
    static map<string, int> roleMap;

    // Constructor
    Role() = default;
    Role(int rNumber, const string &rName, const string &rLevel)
        : roleNumber(rNumber), roleName(rName), roleLevel(rLevel) {};
};
