#pragma once

#include <wx/wx.h>

// Class that displays the login panel/screen
class LoginPanel : public wxPanel{
public:
    LoginPanel(wxWindow* parent);
private:
    void onLogin(wxCommandEvent& event);
};
