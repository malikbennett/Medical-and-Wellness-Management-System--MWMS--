#include <HomePanel.h>
#include <LoginPanel.h>
#include <MainFrame.h>
#include <Settings.h>
#include <Session.h>
#include <Role.h>

LoginPanel::LoginPanel(wxPanel *parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(325, 350))
{
    this->parent = parent;
    buildUI();
}

void LoginPanel::buildUI()
{
    this->SetBackgroundColour(Settings::getInstance().colors.surface);

    const int margin = 20;

    // Create the sizer that will arrange items vertically
    wxBoxSizer *loginSizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(loginSizer);

    wxStaticText *firstHeader = new wxStaticText(this, wxID_ANY, "Welcome Back",wxDefaultPosition,wxDefaultSize,wxALIGN_CENTER);
    firstHeader->SetFont(wxFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    wxStaticText *subText = new wxStaticText(this, wxID_ANY, "Enter your credential to access your account.", wxDefaultPosition,wxDefaultSize,wxALIGN_CENTER);
    subText->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    subText->SetForegroundColour(Settings::getInstance().colors.textSecondaryDark);
    subText->Wrap(300);

    this->usernameField = new wxTextCtrl(this, wxID_ANY, "");
    this->usernameField->SetBackgroundColour(Settings::getInstance().colors.textSecondaryLight);
    this->usernameField->SetForegroundColour(Settings::getInstance().colors.textPrimary);
    this->usernameField->SetHint("Enter username");

    this->passwordField = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
    this->passwordField->SetBackgroundColour(Settings::getInstance().colors.textSecondaryLight);
    this->passwordField->SetForegroundColour(Settings::getInstance().colors.textPrimary);
    this->passwordField->SetHint("Enter password");

    this->loginBtn = new wxButton(this, wxID_OK, "Login");
    this->loginBtn->SetBackgroundColour(Settings::getInstance().colors.primary);
    this->loginBtn->Bind(wxEVT_BUTTON, &LoginPanel::onLogin, this);

    loginSizer->Add(firstHeader, 0, wxEXPAND | wxALL, margin);
    loginSizer->Add(subText, 0, wxEXPAND | wxBOTTOM | wxLEFT | wxRIGHT, margin);
    loginSizer->Add(usernameField, 0, wxEXPAND | wxBOTTOM | wxLEFT | wxRIGHT, margin);
    loginSizer->Add(passwordField, 0, wxEXPAND | wxBOTTOM | wxLEFT | wxRIGHT, margin);
    loginSizer->Add(loginBtn, 0, wxEXPAND | wxALL, margin);

    loginSizer->Layout();
}

void LoginPanel::onLogin(wxCommandEvent &event)
{
    // Gets results from input fields and roleOption

    string usernameStr = usernameField->GetValue().ToStdString();
    string passwordStr = passwordField->GetValue().ToStdString();

    // Logs user into the session
    if (Session::Login(usernameStr, passwordStr) <= 0)
    {
        // Hides Login Panel
        this->Hide();
        Session::GetCurrentUser()->show();
        int roleNumber = Session::GetCurrentUser()->getRole().roleNumber;
        wxPanel* newDashboard = nullptr;
        switch (roleNumber)
        {
        case 1: newDashboard = new AdminDashboard(parent); break;
        case 2: newDashboard = new DoctorDashboard(parent); break;
        case 3: newDashboard = new PsychologistDashboard(parent); break;
        case 4: newDashboard = new DietitianDashboard(parent); break;
        case 5: newDashboard = new NurseDashboard(parent); break;
        case 6: newDashboard = new ReceptionistDashboard(parent); break;
        default: newDashboard = new PatientDashboard(parent); break;
        }
        if (MainFrame* frame = dynamic_cast<MainFrame*>(parent->GetParent()))
        {
            frame->SwitchPanel(newDashboard);
        }
    }
}
