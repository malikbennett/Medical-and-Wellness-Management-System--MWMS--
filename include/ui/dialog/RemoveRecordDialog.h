#pragma once

#include <wx/wx.h>
#include <User.h>
#include <Appointment.h>
#include <UserManager.h>

class RemoveRecordDialog : public wxDialog
{
public:
    RemoveRecordDialog(wxPanel *parent, User *user);
    RemoveRecordDialog(wxPanel *parent, Appointment *apt);
    void EndModal(int retCode) override;

    User* user;
    Appointment* apt;
    wxTextCtrl* dateCtrl;
    wxTextCtrl* timeCtrl;
    wxChoice* statusChoice;
};
