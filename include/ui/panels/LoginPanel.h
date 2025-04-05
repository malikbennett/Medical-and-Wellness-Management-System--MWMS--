#pragma once

#include <wx/wx.h>

// Class that displays the login panel/screen
class LoginPanel : public wxPanel{
public:
    LoginPanel(wxPanel* parentPanel);
    LoginPanel(wxFrame* parentFrame);
private:
    wxPanel *loginPanel;
    wxPanel *imagePanel;
    wxBoxSizer *imageSizer;
    wxBoxSizer *mainSizer;
    wxBoxSizer *loginSizer;
    wxTextCtrl *usernameField;
    wxTextCtrl *passwordField;
    wxChoice *roleOptions;
    wxButton *loginBtn;
    void onLogin(wxCommandEvent &event);
};
