#pragma once

#include <wx/wx.h>
#include <wx/datectrl.h>
#include <wx/dateevt.h>

// Class that displays the login panel/screen
class SignupPanel : public wxPanel{
public:
    // Constructors
    SignupPanel(wxPanel* parent);
    void buildUI();

private:
    wxPanel *parent;
    wxPanel *signupPanel;
    wxBoxSizer *signupSizer;

    wxTextCtrl *usernameField;
    wxTextCtrl *passwordField;
    wxTextCtrl *firstNameField;
    wxTextCtrl *middleNameField;
    wxTextCtrl *lastNameField;
    wxTextCtrl *trnField;
    wxDatePickerCtrl *dobField;
    wxDatePickerCtrl *firstVisitField;
    wxChoice *genderField;
    wxChoice *maritalStatusField;
    wxTextCtrl *nokField;
    wxTextCtrl *nokContactField;
    wxTextCtrl *medHistField;
    wxTextCtrl *emailField;
    wxTextCtrl *phoneField;
    wxTextCtrl *addressField;

    wxButton *signupBtn;
    void onSignup(wxCommandEvent &event);
};
