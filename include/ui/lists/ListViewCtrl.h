
#pragma once

#include <vector>
#include <stdexcept>
#include <iostream> // for cout and cerr

#include <UserManager.h>
#include <wx/wx.h>
#include <wx/listctrl.h>

using namespace std;

class ListView : public wxListCtrl
{
public:
    ListView(wxPanel *parent, wxWindowID id, const wxPoint &pos, const wxSize &size) : wxListCtrl(parent, id, pos, size, wxLC_REPORT | wxLC_VIRTUAL)
    {
        this->usrfields = UserManager::getFields(UserManager::userInfoPath);
        this->empfields = UserManager::getFields(UserManager::employeeInfoPath);
        this->patfields = UserManager::getFields(UserManager::patientInfoPath);
    };

    void loadEmployeeFields()
    {
        vector<UserDataBuffer *> allUsers = UserManager::getAllUsers();
        this->users.clear();

        // Only keep users who are NOT patients (i.e., roleId != 7)
        for (auto *user : allUsers)
        {
            if (user->roleId != 7)
            {
                this->users.push_back(user);
            }
        }
        if (users.empty())
        {
            wxMessageBox("No users found.");
            return;
        }
        // Clear previous columns
        this->ClearAll();
        for (size_t i = 0; i < usrfields.size() && i < 6; ++i)
        {
            this->AppendColumn(usrfields[i]);
        }
        for (size_t i = 1; i < empfields.size() && i <= 11; ++i)
        {
            this->AppendColumn(empfields[i]);
        }
    }
    void loadPatientFields()
    {
        auto allUsers = UserManager::getAllUsers();
        this->users.clear();

        // Only keep users who are patients (i.e., roleId = 7)
        for (auto *user : allUsers)
        {
            if (user->roleId == 7)
            {
                this->users.push_back(user);
            }
        }
        if (users.empty())
        {
            wxMessageBox("No users found.");
            return;
        }
        // Clear previous columns
        this->ClearAll();
        for (size_t i = 0; i < usrfields.size() && i < 6; ++i)
        {
            this->AppendColumn(usrfields[i]);
        }
        for (size_t i = 1; i < patfields.size() && i <= 15; ++i)
        {
            this->AppendColumn(patfields[i]);
        }
    }

    virtual wxString OnGetItemText(long index, long column) const override
    {
        UserDataBuffer *user = this->users.at(index);
        switch (column)
        {
        case 0:
            return wxString::Format("%d", user->userNumber);
        case 1:
            return trimString(user->username);
        case 2:
            return trimString(user->encryptedPassword);
        case 3:
            return wxString::Format("%d", user->roleId);
        case 4:
            return wxString::Format("%d", user->attemptsRemainding);
        case 5:
            return (user->isLocked) ? "yes" : "no";
        }
        // Only access Employee Profile fields
        if (user->roleId != 7)
        {
            switch (column)
            {
            case 6:
                return user->ProfileRecords[1];
            case 7:
                return user->ProfileRecords[2];
            case 8:
                return user->ProfileRecords[3];
            case 9:
                return user->ProfileRecords[4];
            case 10:
                return user->ProfileRecords[5];
            case 11:
                return user->ProfileRecords[6];
            case 12:
                return user->ProfileRecords[7];
            case 13:
                return user->ProfileRecords[8];
            case 14:
                return user->ProfileRecords[9];
            case 15:
                return user->ProfileRecords[10];
            case 16:
                return user->ProfileRecords[11];
            }
        }
        // Only access Patient Profile fields
        if (user->roleId == 7)
        {
            switch (column)
            {
            case 6:
                return user->ProfileRecords[1];
            case 7:
                return user->ProfileRecords[2];
            case 8:
                return user->ProfileRecords[3];
            case 9:
                return user->ProfileRecords[4];
            case 10:
                return user->ProfileRecords[5];
            case 11:
                return user->ProfileRecords[6];
            case 12:
                return user->ProfileRecords[7];
            case 13:
                return user->ProfileRecords[8];
            case 14:
                return user->ProfileRecords[9];
            case 15:
                return user->ProfileRecords[10];
            case 16:
                return user->ProfileRecords[11];
            case 17:
                return user->ProfileRecords[12];
            case 18:
                return user->ProfileRecords[13];
            case 19:
                return user->ProfileRecords[14];
            case 20:
                return user->ProfileRecords[15];
            }
        }
        return " ";
    }

    void RefreshAfterUpdate()
    {
        this->SetItemCount(this->users.size());
        this->Refresh();
    }

private:
    vector<string> usrfields;
    vector<string> empfields;
    vector<string> patfields;
    vector<UserDataBuffer *> users;
};
