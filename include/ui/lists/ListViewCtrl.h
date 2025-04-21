
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
    ListView(wxPanel *parent, wxWindowID id, const wxPoint &pos, const wxSize &size);
    void loadEmployeeFields();
    void loadPatientFields();
    void loadAppointmentsFields();
    virtual wxString OnGetItemText(long index, long column) const override;
    void RefreshAfterUpdate();

private:
    vector<string> usrfields;
    vector<string> empfields;
    vector<string> patfields;
    vector<string> aptfields;
    vector<User *> users;
    vector<Appointment *> apts;
    wxPanel *parent;
    int index;
    void OnItemActivated(wxListEvent &event);
};
