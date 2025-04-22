#pragma once

#include <wx/wx.h>

// Class that displays the login panel/screen
class LoginPanel : public wxPanel{
public:
    // Constructors
    LoginPanel(wxPanel* parent);
    void buildUI();

private:
    wxPanel *parent;
    wxPanel *loginPanel;
    wxBoxSizer *loginSizer;
    wxTextCtrl *usernameField;
    wxTextCtrl *passwordField;
    wxButton *loginBtn;
    void onLogin(wxCommandEvent &event);
};
