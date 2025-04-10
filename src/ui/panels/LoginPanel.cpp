#include <RenderText.h>
#include <LoginPanel.h>
#include <MainFrame.h>
#include <Settings.h>
#include <Session.h>
#include <Role.h>
#include <RenderText.h>

LoginPanel::LoginPanel(wxPanel *parentPanel) : wxPanel(parentPanel)
{
    const int margin = 20;

    // Main Login Panel (centered)
    this->loginPanel = new wxPanel(parentPanel, wxID_ANY, wxDefaultPosition, wxSize(350, 400));
    this->loginPanel->SetBackgroundColour(Settings::getInstance().colors.surface);

    // Create the sizer that will arrange items vertically inside loginPanel

    this->loginSizer = new wxBoxSizer(wxVERTICAL);
    this->loginPanel->SetSizer(loginSizer);

    // text
    wxStaticText *firstHeader = RenderText::getInstance().createText(
        this->loginPanel, "Welcome Back", TEXT_HEADING, wxALIGN_CENTER_HORIZONTAL);
    wxStaticText *subText = RenderText::getInstance().createText(
        this->loginPanel, "Enter your credential to access your account.", TEXT_PARAGRAPH, wxALIGN_CENTER_HORIZONTAL);
    subText->SetForegroundColour(Settings::getInstance().colors.textSecondaryDark);
    subText->Wrap(300);

    // Input Fields
    this->usernameField = new wxTextCtrl(this->loginPanel, wxID_ANY, "");
    this->usernameField->SetBackgroundColour(Settings::getInstance().colors.textSecondaryLight);
    this->usernameField->SetForegroundColour(Settings::getInstance().colors.textPrimary);
    this->usernameField->SetHint("Enter username");
    this->usernameField->SetToolTip("Enter username");
    this->passwordField = new wxTextCtrl(this->loginPanel, wxID_ANY, "");
    this->passwordField->SetBackgroundColour(Settings::getInstance().colors.textSecondaryLight);
    this->passwordField->SetForegroundColour(Settings::getInstance().colors.textPrimary);
    this->passwordField->SetHint("Enter password");
    this->passwordField->SetToolTip("Enter password");

    this->loginBtn = new wxButton(this, wxID_OK, "Login");
    this->loginBtn->SetBackgroundColour(Settings::getInstance().colors.primary);
    this->loginBtn->Bind(wxEVT_BUTTON, &LoginPanel::onLogin, this);

    this->loginPanel->Layout();

    // Add elements to sizer
    this->loginSizer->Add(firstHeader, 0, wxEXPAND | wxALL, margin);
    this->loginSizer->Add(subText, 0, wxEXPAND | wxBOTTOM | wxLEFT | wxRIGHT, margin);
    this->loginSizer->Add(this->usernameField, 1, wxEXPAND | wxALIGN_CENTER | wxBOTTOM | wxLEFT | wxRIGHT, margin);
    this->loginSizer->Add(this->passwordField, 1, wxEXPAND | wxALIGN_CENTER | wxBOTTOM | wxLEFT | wxRIGHT, margin);
    this->loginSizer->Add(this->loginBtn, 1, wxEXPAND | wxALL, margin);

    // Main sizer to center loginPanel on screen
    this->mainSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* center = new wxBoxSizer(wxHORIZONTAL);
    center->Add(this->loginPanel, 0, wxALIGN_CENTER);
    this->mainSizer->Add(center, 1, wxALIGN_CENTER);

    // Apply to parent
    parentPanel->SetSizerAndFit(this->mainSizer);
}

LoginPanel::LoginPanel(wxFrame *parentFrame) : wxPanel(parentFrame) {}

void LoginPanel::onLogin(wxCommandEvent &event)
{
    // Gets results from input fields and roleOption

    string usernameStr = usernameField->GetValue().ToStdString();
    string passwordStr = passwordField->GetValue().ToStdString();
    string roleStr = roleOptions->GetStringSelection().ToStdString();

    // Logs user into the session
    if(Session::Login(usernameStr, passwordStr) <= 0)
    {
        Session::GetCurrentUser()->show();
    }
}
