#include <Session.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <Encryption.h>

User *Session::currentUser = nullptr;
string Session::userInfoPath = "../../data/UserInfo.csv";
string Session::userRolePath = "../../data/UserRoles.csv";

User *Session::GetCurrentUser()
{
    return currentUser;
}

void Session::SetCurrentUser(int userId, const string &username, const string &password, Role role)
{
    if (currentUser)
        delete currentUser;
    currentUser = new User(userId, username, password, role);
}

Result Session::Login(const string &username, const string &password, const string &role)
{
    try
    {
        // Opens User Info file
        ifstream file(userInfoPath);
        if (!file.is_open())
        {
            // Returns an error is file did not open successfully
            return Result(StatusCode::FileError);
        }
        string line;
        getline(file, line);
        string key;
        Encrypt::getInstance().readKeyFromFile("../../data/encryption.key", key);

        while (getline(file, line))
        {
            stringstream ss(line);
            string token;
            vector<string> fields;

            while (getline(ss, token, ','))
            {
                fields.push_back(token);
            }

            if (fields.size() != 4)
                continue;

            string fileUsername = fields[1];
            string filePassword = fields[2];
            int fileRoleId = stoi(fields[3]);

            if (fileUsername != username)
                continue;

            string encryptedInputPassword = Encrypt::getInstance().xorEncryptDecrypt(password, key);
            if (encryptedInputPassword != filePassword)
            {
                return Result(StatusCode::IncorrectPassword);
            }

            if (Role::roleMap.find(role) == Role::roleMap.end())
            {
                return Result(StatusCode::InvalidRole);
            }

            if (fileRoleId != Role::roleMap[role])
            {
                return Result(StatusCode::RoleMismatch);
            }

            Role userRole = loadRole(userRolePath, fileRoleId);
            SetCurrentUser(stoi(fields[0]), fileUsername, filePassword, userRole);
            return Result(StatusCode::Ok);
        }
        return Result(StatusCode::UsernameNotFound);
    }
    catch (const exception &e)
    {
        cerr << "Login error: " << e.what() << endl;
        return Result(StatusCode::UnknownError);
    }
}

void Session::Logout()
{
    if (currentUser)
    {
        delete currentUser;
        currentUser = nullptr;
    }
}

Role Session::loadRole(const string &filePath, int roleNumber)
{
    try
    {
        ifstream file(filePath);
        if (file.fail())
        {
            throw runtime_error("Role data file failed to open");
        }
        string line;
        getline(file, line);
        while (getline(file, line))
        {
            stringstream ss(line);
            string token;
            vector<string> fields;
            while (getline(ss, token, ','))
            {
                fields.push_back(token);
            }
            if (fields.size() == 3)
            {
                int roleID = stoi(fields[0]);
                if (roleID == roleNumber)
                {
                    file.close();
                    return Role(roleID, fields[1], fields[2]);
                }
            }
        }
        file.close();
    }
    catch (const exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return Role();
}
