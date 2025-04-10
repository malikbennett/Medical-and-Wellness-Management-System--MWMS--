#pragma once

#include <wx/wx.h>

// Class that displays the login panel/screen
class LoginPanel : public wxPanel{
public:
    // Constructors
    LoginPanel(wxPanel* parentPanel, wxPanel* nextPanel);
private:
    wxPanel *loginPanel;
    wxPanel *nextPanel;
    wxBoxSizer *imageSizer;
    wxBoxSizer *mainSizer;
    wxBoxSizer *loginSizer;
    wxTextCtrl *usernameField;
    wxTextCtrl *passwordField;
    wxChoice *roleOptions;
    wxButton *loginBtn;
    void onLogin(wxCommandEvent &event);
    void hide();
};
