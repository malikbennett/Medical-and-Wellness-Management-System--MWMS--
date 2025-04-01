#include <loginpanel.h>

LoginPanel::LoginPanel(wxWindow* parent) : wxPanel(parent) {
    new wxStaticText(this, wxID_ANY, "Username:", wxPoint(20, 20));
    wxTextCtrl* usernameField = new wxTextCtrl(this, wxID_ANY, "", wxPoint(100, 20), wxSize(150, -1));

    wxButton* loginBtn = new wxButton(this, wxID_OK, "Login", wxPoint(100, 60));
}
