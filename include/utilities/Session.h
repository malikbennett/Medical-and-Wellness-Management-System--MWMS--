#pragma once
#include "User.h"

class Session {
public:
    // Return the current active user in session
    static User* GetCurrentUser();
    // Logs in the respective user in session
    static void SetCurrentUser(int userId, const std::string& username, const std::string& password);
    static void Logout();

private:
    static User* currentUser;
};

User* Session::currentUser = nullptr;

User* Session::GetCurrentUser() {
    return currentUser;
}

void Session::SetCurrentUser(int userId, const std::string& username, const std::string& password) {
    if (currentUser) delete currentUser;
    currentUser = new User(userId, username, password);
}

void Session::Logout() {
    if (currentUser) {
        delete currentUser;
        currentUser = nullptr;
    }
}
