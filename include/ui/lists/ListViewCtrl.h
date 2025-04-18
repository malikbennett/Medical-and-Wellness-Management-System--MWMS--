
#pragma once

#include <vector>
#include <stdexcept>
#include <iostream>
#include <Helper.h>
#include <UserManager.h>
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <Appointment.h>
#include <Employee.h>
#include <Patient.h>

using namespace std;

class ListView : public wxListCtrl
{
public:
    ListView(wxPanel *parent, wxWindowID id, const wxPoint &pos, const wxSize &size) : wxListCtrl(parent, id, pos, size, wxLC_REPORT | wxLC_VIRTUAL)
    {
        this->usrfields = getFileFields(UserManager::userInfoPath);
        this->empfields = getFileFields(UserManager::employeeInfoPath);
        this->patfields = getFileFields(UserManager::patientInfoPath);
        this->aptfields = getFileFields(Appointment::aptInfoPath);
    };
    void loadEmployeeFields()
    {
        auto allUsers = UserManager::getAllUsers();
        this->users.clear();
        // Only keep users who are NOT patients (i.e., roleId != 7)
        for (auto *user : allUsers)
        {
            if (user->getRole().roleNumber != 7)
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
            if (user->getRole().roleNumber == 7)
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
    void loadAppointmentsFields()
    {
        auto allApts = Appointment::getAllApt();
        const User *user = Session::GetCurrentUser();
        const Patient *pat = dynamic_cast<const Patient *>(user);
        this->apts.clear();
        if (pat)
        {
            for (auto *apt : allApts)
            {
                // Checks for patient
                if (apt->getPatientNumber() == pat->getPatientNumber())
                    this->apts.push_back(apt);
            }
        }
        if (this->apts.empty())
        {
            wxMessageBox("No Appointments found.");
            return;
        }
        for (size_t i = 0; i < this->aptfields.size() && i <= 5; ++i)
        {
            this->AppendColumn(this->aptfields[i]);
        }
    }

    virtual wxString OnGetItemText(long index, long column) const override
    {
        if (!this->apts.empty())
        {
            Appointment *apt = this->apts.at(index);
            string statusStr;
            if (apt->getStatus() == 0)
            {
                statusStr = "Completed";
            }
            else if (apt->getStatus() == 1)
            {
                statusStr = "Scheduled";
            }
            else
            {
                statusStr = "Cancelled";
            }
            switch (column)
            {
            case 0:
                return to_string(apt->getAppointmentNumber());
            case 1:
                return to_string(apt->getPatientNumber());
            case 2:
                return to_string(apt->getDoctorNumber());
            case 3:
                return Date::toString(apt->getAppointmentDate());
            case 4:
                return apt->getAppointmentTime();
            case 5:
                return statusStr;
            }
        }
        else if (!this->users.empty())
        {
            User *user = this->users.at(index);
            switch (column){
            case 0:
                return wxString::Format("%d", user->getUserNumber());
            case 1:
                return trimString(user->getUsername());
            case 2:
                return trimString(user->getPassword());
            case 3:
                return wxString::Format("%d", user->getRole().roleNumber);
            case 4:
                return wxString::Format("%d", user->getAttemptsRemaining());
            case 5:
                return (user->locked()) ? "yes" : "no";
            }
            // Only access Employee Profile fields
            if (user->getRole().roleNumber != 7)
            {
                switch (column)
                {
                case 6:
                    return user->getProfileRecords()[1];
                case 7:
                    return user->getProfileRecords()[2];
                case 8:
                    return user->getProfileRecords()[3];
                case 9:
                    return user->getProfileRecords()[4];
                case 10:
                    return user->getProfileRecords()[5];
                case 11:
                    return user->getProfileRecords()[6];
                case 12:
                    return user->getProfileRecords()[7];
                case 13:
                    return user->getProfileRecords()[8];
                case 14:
                    return user->getProfileRecords()[9];
                case 15:
                    return user->getProfileRecords()[10];
                case 16:
                    return user->getProfileRecords()[11];
                }
            }
            // Only access Patient Profile fields
            if (user->getRole().roleNumber == 7)
            {
                switch (column)
                {
                case 6:
                    return user->getProfileRecords()[1];
                case 7:
                    return user->getProfileRecords()[2];
                case 8:
                    return user->getProfileRecords()[3];
                case 9:
                    return user->getProfileRecords()[4];
                case 10:
                    return user->getProfileRecords()[5];
                case 11:
                    return user->getProfileRecords()[6];
                case 12:
                    return user->getProfileRecords()[7];
                case 13:
                    return user->getProfileRecords()[8];
                case 14:
                    return user->getProfileRecords()[9];
                case 15:
                    return user->getProfileRecords()[10];
                case 16:
                    return user->getProfileRecords()[11];
                case 17:
                    return user->getProfileRecords()[12];
                case 18:
                    return user->getProfileRecords()[13];
                case 19:
                    return user->getProfileRecords()[14];
                case 20:
                    return user->getProfileRecords()[15];
                }
            }
        }
        return " ";
    }

    void RefreshAfterUpdate()
    {
        if (!this->apts.empty())
        {
            this->SetItemCount(this->apts.size());
        }
        else if (!this->users.empty())
        {
            this->SetItemCount(this->users.size());
        }
        this->Refresh();
    }

private:
    vector<string> usrfields;
    vector<string> empfields;
    vector<string> patfields;
    vector<string> aptfields;
    vector<User *> users;
    vector<Appointment *> apts;
};
