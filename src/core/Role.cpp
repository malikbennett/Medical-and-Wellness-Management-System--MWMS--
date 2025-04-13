#include <Role.h>
#include <wx/wx.h>
#include <fstream>
#include <sstream>
#include <vector>

string Role::userRolePath = "../../data/UserRoles.csv";

Role::Role(int rNumber, const string &rName, const string &rLevel)
    : roleNumber(rNumber), roleName(rName), roleLevel(rLevel) {};

Role Role::LoadRoleFromFile(const string &filePath, int roleNumber)
{
    try
    {
        // Open role data file
        ifstream file(filePath);
        // Checks if the file failed to open
        if (file.fail())
        {
            // If file failed an error is thrown
            wxMessageBox("Role data file failed to open", "File Error", wxICON_ERROR);
            throw runtime_error("Role data file failed to open");
        }
        // Variable to store record
        string line;
        // Skips to first line
        getline(file, line);
        // Loops through each store
        while (getline(file, line))
        {
            // Initialize a stringstream to parse record into individual fields
            stringstream ss(line);
            // Variable to store each field's value
            string token;
            // Vector which stores each token for later access
            vector<string> fields;
            // Loops through the stringstream and store each value seperated by a "," into token variable
            while (getline(ss, token, ','))
            {
                // Adds value into field variable
                fields.push_back(token);
            }
            // If the field size(amount of columns) does not match 3; that means there is an error with that record and it should be skipped
            if (fields.size() != 3)
                continue;
            // convert roleNumber from database into an int and stores it
            int roleID = stoi(fields[0]);
            // Checks if roleNumbers match
            if (roleID == roleNumber)
            {
                // Closes file
                file.close();
                // Returns an instance of type Role
                return Role(roleID, fields[1], fields[2]);
            }
        }
        // Closes file
        file.close();
    }
    catch (const exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    // Returns empty Role if role was not created successfully
    return Role();
}
