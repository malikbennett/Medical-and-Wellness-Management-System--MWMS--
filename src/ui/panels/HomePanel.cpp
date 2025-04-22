#include <HomePanel.h>
#include <MainFrame.h>
#include <LoginPanel.h>
#include <SignupPanel.h>
#include <Settings.h>
#include <Helper.h>
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
    if (emp)
    {
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
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DFACE));

    infoText = new wxStaticText(this, wxID_ANY, "Don't have an account?");
    this->actionBtn = new wxButton(this, wxID_ANY, "Signup");
    this->actionBtn->Bind(wxEVT_BUTTON, &Footer::updateForSignup, this);

    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(infoText, 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);
    sizer->AddStretchSpacer(1);
    sizer->Add(this->actionBtn, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);

    SetSizer(sizer);
}

void Footer::onLogout(wxCommandEvent &event)
{
    Session::Logout();
    wxPanel *loginPanel = new LoginPanel(this->parent);
    if (MainFrame *frame = dynamic_cast<MainFrame *>(this->parent->GetParent()))
    {
        frame->SwitchPanel(loginPanel);
    }
    SetState(FooterState::LOGIN);
}

void Footer::updateForSignup(wxCommandEvent &event)
{
    wxPanel *signUpPanel = new SignupPanel(this->parent);
    if (MainFrame *frame = dynamic_cast<MainFrame *>(this->parent->GetParent()))
    {
        frame->SwitchPanel(signUpPanel);
    }
    SetState(FooterState::SIGNUP);
}

void Footer::updateForLogin(wxCommandEvent &event)
{
    wxPanel *loginPanel = new LoginPanel(this->parent);
    if (MainFrame *frame = dynamic_cast<MainFrame *>(this->parent->GetParent()))
    {
        frame->SwitchPanel(loginPanel);
    }
    SetState(FooterState::LOGIN);
}

void Footer::updateForDashboard()
{
    SetState(FooterState::DASHBOARD);
}

void Footer::SetState(FooterState state)
{
    switch (state)
    {
    case FooterState::LOGIN:
        this->infoText->SetLabel("Don't have an account?");
        this->actionBtn->SetLabel("Signup");
        this->actionBtn->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DFACE));
        this->actionBtn->Unbind(wxEVT_BUTTON,&Footer::updateForLogin, this);
        this->actionBtn->Bind(wxEVT_BUTTON, &Footer::updateForSignup, this);
        break;

        case FooterState::SIGNUP:
        this->infoText->SetLabel("Already have an account?");
        this->actionBtn->SetLabel("Login");
        this->actionBtn->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DFACE));
        this->actionBtn->Unbind(wxEVT_BUTTON, &Footer::updateForSignup, this);
        this->actionBtn->Bind(wxEVT_BUTTON, &Footer::updateForLogin, this);
        break;

    case FooterState::DASHBOARD:
        this->infoText->SetLabel("Medical And Wellness Management System");
        this->actionBtn->SetLabel("Logout");
        this->actionBtn->SetBackgroundColour(Settings::getInstance().colors.error);
        this->actionBtn->Unbind(wxEVT_BUTTON,&Footer::updateForLogin, this);
        this->actionBtn->Bind(wxEVT_BUTTON, &Footer::onLogout, this);
        break;
    }
    actionBtn->Show();
    Layout();
}

wxButton* Footer::GetActionButton() {
    return this->actionBtn;
}
