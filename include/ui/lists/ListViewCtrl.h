
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
        auto allUsers = UserManager::getAllUsers();
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
        IUserProfile *profile = UserManager::getProfileInfo(user->roleId, user->userNumber);
        EmployeeProfile *ep = nullptr;
        PatientProfile *pp = nullptr;

        if (user->roleId != 7)
        {
            ep = dynamic_cast<EmployeeProfile *>(profile);
        }
        else
        {
            pp = dynamic_cast<PatientProfile *>(profile);
        }

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

        // Only access EmployeeProfile fields if ep is valid
        if (ep != nullptr)
        {
            switch (column)
            {
            case 6:
                return ep->records[1];
            case 7:
                return ep->records[2];
            case 8:
                return ep->records[3];
            case 9:
                return ep->records[4];
            case 10:
                return ep->records[5];
            case 11:
                return ep->records[6];
            case 12:
                return ep->records[7];
            case 13:
                return ep->records[8];
            case 14:
                return ep->records[9];
            case 15:
                return ep->records[10];
            case 16:
                return ep->records[11];
            }
        }
        if (pp != nullptr)
        {
            switch (column)
            {
            case 6:
                return pp->records[1];
            case 7:
                return pp->records[2];
            case 8:
                return pp->records[3];
            case 9:
                return pp->records[4];
            case 10:
                return pp->records[5];
            case 11:
                return pp->records[6];
            case 12:
                return pp->records[7];
            case 13:
                return pp->records[8];
            case 14:
                return pp->records[9];
            case 15:
                return pp->records[10];
            case 16:
                return pp->records[11];
            case 17:
                return pp->records[12];
            case 18:
                return pp->records[13];
            case 19:
                return pp->records[14];
            case 20:
                return pp->records[15];
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
