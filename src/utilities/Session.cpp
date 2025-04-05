#include <Session.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <Encryption.h>

User* Session::currentUser = nullptr;
string Session::userInfoPath = "../../data/UserInfo.csv";
string Session::userRolePath = "../../data/UserRoles.csv";

User* Session::GetCurrentUser() {
    return currentUser;
}

void Session::SetCurrentUser(int userId, const string& username, const string& password, Role role) {
    if (currentUser) delete currentUser;
    currentUser = new User(userId, username, password, role);
}
string Session::Login(const string &username, const string &password, const string &role) {
    try
    {
        ifstream file(userInfoPath);
        if(file.fail()){
            throw runtime_error("Could not open user info");
        }
        string line;
        getline(file, line);
        while (getline(file, line))
        {
            stringstream ss(line);
            string token;
            vector<string> field;
            while (getline(ss, token, ','))
            {
                field.push_back(token);
            }
            if(field.size() == 4){
                // Checks username
                if( field[1] == username){
                    // Checks password
                    // Converts Plain-Text to encrypted HEX and campare to whats is store in database
                    string key;
                    Encrypt::getInstance().readKeyFromFile("../../data/encryption.key", key);
                    string encryptPassword = Encrypt::getInstance().xorEncryptDecrypt(password, key);
                    if (encryptPassword == field[2])
                    {
                        // Checks Role
                        if(stoi(field[3]) == Role::roleMap[role]){
                            SetCurrentUser(stoi(field[0]), field[1], field[2], loadRole(userRolePath, stoi(field[3])));
                        }
                    }
                }
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

}
void Session::Logout() {
    if (currentUser) {
        delete currentUser;
        currentUser = nullptr;
    }
}

Role Session::loadRole(const string& filePath, int roleNumber) {
    try {
        ifstream file(filePath);
        if(file.fail()) {
            throw runtime_error("Role data file failed to open");
        }
        string line;
        getline(file, line);
        while (getline(file, line))
        {
            stringstream ss(line);
            string token;
            vector<string> fields;
            while(getline(ss, token, ',')) {
                fields.push_back(token);
            }
            if(fields.size() == 3) {
                int roleID = stoi(fields[0]);
                if (roleID == roleNumber) {
                    return Role(roleID, fields[1], fields[2]);
                }
            }
        }
    } catch(const exception& e) {
        std::cerr << e.what() << '\n';
    }

    return Role();
}
