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
    // File path to the role information database
    static string userRolePath;
    // Constructors
    Role() = default;
    Role(const Role&) = default;
    Role(int rNumber, const string &rName, const string &rLevel);
    // Gets the role data from the role database
    static Role LoadRoleFromFile(const string &filePath, int roleNumber);
};
