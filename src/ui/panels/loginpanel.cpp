#include <loginpanel.h>

LoginPanel::LoginPanel(wxWindow* parent) : wxPanel(parent) {
    new wxStaticText(this, wxID_ANY, "Login", wxPoint(20, 20));
    new wxStaticText(this, wxID_ANY, "Username:", wxPoint(20, 60));
    wxTextCtrl* usernameField = new wxTextCtrl(this, wxID_ANY, "", wxPoint(20, 80), wxSize(150, -1));
    new wxStaticText(this, wxID_ANY, "Password:", wxPoint(20, 120));
    wxTextCtrl* passwordField = new wxTextCtrl(this, wxID_ANY, "", wxPoint(20, 140), wxSize(150, -1), wxTE_PASSWORD);

    wxArrayString roles;
    roles.Add("Admin");
    roles.Add("Doctor");
    roles.Add("Nurse");
    roles.Add("Dietitian");
    roles.Add("Psychologist/Councillor");
    roles.Add("Receptionist");
    roles.Add("Patient");

    wxChoice *roleOptions = new wxChoice(this, wxID_ANY, wxPoint(100, 260), wxSize(100, -1), roles);
    roleOptions->Select(6);
    wxButton* loginBtn = new wxButton(this, wxID_OK, "Login", wxPoint(20, 300));
}
