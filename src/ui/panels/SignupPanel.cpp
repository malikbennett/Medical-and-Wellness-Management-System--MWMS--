
#include <HomePanel.h>
#include <SignupPanel.h>
#include <MainFrame.h>
#include <Settings.h>
#include <Session.h>
#include <Helper.h>
#include <Role.h>


SignupPanel::SignupPanel(wxPanel *parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(640, 360))
{
    this->parent = parent;
    buildUI();
}

void SignupPanel::buildUI()
{
    const int margin = 15;
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* header = new wxStaticText(this, wxID_ANY, "SignUp",wxDefaultPosition,wxDefaultSize,wxALIGN_CENTER);
    header->SetFont(wxFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    mainSizer->Add(header,  1, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, margin);

    wxFlexGridSizer* gridSizer = new wxFlexGridSizer(4, margin, margin);
    gridSizer->AddGrowableCol(1, 1); // Text input 1
    gridSizer->AddGrowableCol(3, 1); // Text input 2

    ADD_PAIR(this, gridSizer, "Username", usernameField, "Password", passwordField);
    ADD_PAIR(this, gridSizer, "First Name", firstNameField, "Middle Name", middleNameField);
    ADD_PAIR(this, gridSizer, "Last Name", lastNameField, "TRN", trnField);

    gridSizer->Add(new wxStaticText(this, wxID_ANY, "Date of Birth"), 0, wxALL);
    dobField = new wxDatePickerCtrl(this, wxID_ANY);
    gridSizer->Add(dobField, 1, wxEXPAND | wxALL);

    gridSizer->Add(new wxStaticText(this, wxID_ANY, "First Visit"), 0, wxALL);
    firstVisitField = new wxDatePickerCtrl(this, wxID_ANY);
    gridSizer->Add(firstVisitField, 1, wxEXPAND | wxALL);

    gridSizer->Add(new wxStaticText(this, wxID_ANY, "Gender:"), 0, wxALL);
    wxArrayString gender;
    gender.Add("M");
    gender.Add("F");
    genderField = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, gender);
    gridSizer->Add(genderField, 0, wxALL | wxALIGN_LEFT);


    gridSizer->Add(new wxStaticText(this, wxID_ANY, "Martial Status"), 0, wxALL);
    wxArrayString status;
    status.Add("Married");
    status.Add("Single");
    status.Add("Separated");
    status.Add("Divorced");
    status.Add("Other");
    maritalStatusField = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, status);
    gridSizer->Add(maritalStatusField, 0, wxALL | wxALIGN_LEFT);

    ADD_PAIR(this, gridSizer, "Next of Kin", nokField, "NOK Contact", nokContactField);
    ADD_PAIR(this, gridSizer, "Medical History", medHistField, "Email", emailField);
    ADD_PAIR(this, gridSizer, "Phone Number", phoneField, "Address", addressField);

    mainSizer->Add(gridSizer, 1, wxEXPAND | wxLEFT | wxRIGHT, margin);

    signupBtn = new wxButton(this, wxID_OK, "Create Account");
    signupBtn->Bind(wxEVT_BUTTON, &SignupPanel::onSignup, this);
    mainSizer->Add(signupBtn, 0, wxALIGN_CENTER | wxALL, margin);

    SetSizer(mainSizer);
    mainSizer->Layout();
}

void SignupPanel::onSignup(wxCommandEvent &event)
{
    vector<string> profile = {
        usernameField->GetValue().ToStdString(),
        passwordField->GetValue().ToStdString(),
        firstNameField->GetValue().ToStdString(),
        middleNameField->GetValue().ToStdString(),
        lastNameField->GetValue().ToStdString(),
        trnField->GetValue().ToStdString(),
        dobField->GetValue().Format("%Y-%m-%d").ToStdString(),
        firstVisitField->GetValue().Format("%Y-%m-%d").ToStdString(),
        genderField->GetStringSelection().ToStdString(),
        maritalStatusField->GetStringSelection().ToStdString(),
        nokField->GetValue().ToStdString(),
        nokContactField->GetValue().ToStdString(),
        medHistField->GetValue().ToStdString(),
        emailField->GetValue().ToStdString(),
        phoneField->GetValue().ToStdString(),
        addressField->GetValue().ToStdString()
    };

    // Example signup call
    if (Session::Signup(profile) <= 0)
    {
        this->Hide();
        Session::GetCurrentUser()->show();
        PatientDashboard* newDashboard = new PatientDashboard(parent);
        if (MainFrame* frame = dynamic_cast<MainFrame*>(parent->GetParent()))
        {
            frame->SwitchPanel(newDashboard);
        }
    }
}
