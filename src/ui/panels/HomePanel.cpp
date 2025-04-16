#include <HomePanel.h>
#include <MainFrame.h>
#include <Settings.h>
#include <Employee.h>
#include <Patient.h>
#include <Session.h>
#include <sstream>
#include <iostream>

/* ---------------- Menu ---------------- */
Menu::Menu(wxPanel *parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(200, 50))
{
    this->parent = parent;
    buildUI();
}
void Menu::buildUI()
{
    const User *user = Session::GetCurrentUser();
    const Employee *emp = dynamic_cast<const Employee *>(user);
    const Patient *pat = dynamic_cast<const Patient *>(user);

    wxBoxSizer *menuSizer = new wxBoxSizer(wxHORIZONTAL);
    this->SetSizer(menuSizer);

    // Welcome User Text
    stringstream ss;
    if (emp){
        ss << "Welcome, " << emp->getFirstName() << " " << emp->getMiddleName() << " " << emp->getLastName()
        << " (" << emp->getRole().roleName << ")";
    }
    else if (pat)
    {
        ss << "Welcome, " << pat->getPatientFirstName() << " " << pat->getPatientMiddleName() << " " << pat->getPatientLastName()
        << " (" << pat->getRole().roleName << ")";
    }

    wxStaticText *welcomeText = new wxStaticText(this, wxID_ANY, ss.str(), wxDefaultPosition, wxDefaultSize);
    welcomeText->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    menuSizer->Add(welcomeText, 1, wxEXPAND | wxALL | wxALIGN_CENTER, 5);
}

/* ---------------- Footer Dashboard ---------------- */
Footer::Footer(wxPanel *parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(200, 50))
{
    this->parent = parent;
    buildUI();
}
void Footer::buildUI()
{
    // Footer panel
    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
    this->logoutBtn = new wxButton(this, wxID_OK, "Logout");
    this->logoutBtn->SetBackgroundColour(Settings::getInstance().colors.error);
    this->logoutBtn->Bind(wxEVT_BUTTON, &Footer::onLogout, this);

    sizer->AddStretchSpacer();
    sizer->Add(this->logoutBtn, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
    this->SetSizer(sizer);
}

void Footer::onLogout(wxCommandEvent &event)
{
    cout << "Logout\n";
    Session::Logout();
    wxPanel *loginPanel = new LoginPanel(this->parent);
    if (MainFrame *frame = dynamic_cast<MainFrame *>(this->parent->GetParent()))
    {
        frame->SwitchPanel(loginPanel);
    }
};
