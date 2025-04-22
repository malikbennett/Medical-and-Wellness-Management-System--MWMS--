#pragma once

#include <wx/wx.h>
#include <User.h>
#include <Appointment.h>
#include <UserManager.h>

class ActionDialog : public wxDialog {
public:
    ActionDialog(wxPanel *parent, Appointment *apt, User *user,Prescription* pres);

private:
    Appointment* apt;
    Prescription* pres;
    User* user;
    EditRecordPanel* editPanel;
    wxPanel* removePanel;
    wxBoxSizer* sizer;

    void OnShowEdit(wxCommandEvent &);

    void OnShowRemove(wxCommandEvent&);
};
