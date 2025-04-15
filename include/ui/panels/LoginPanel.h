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
