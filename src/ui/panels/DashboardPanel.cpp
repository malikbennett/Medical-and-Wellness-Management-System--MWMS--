#include <DashboardPanel.h>
#include <MainFrame.h>
#include <RenderText.h>
#include <Settings.h>
#include <Session.h>
#include <iostream>

/* ---------------- Admin Dashboard ---------------- */
AdminDashboard::AdminDashboard(wxPanel *parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(400, 100))
{
    this->parent = parent;
    buildUI();
}
void AdminDashboard::buildUI()
{
    std::cout << "Started\n";
    this->notebook = new wxNotebook(this, wxID_ANY);

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(sizer);

    // Home Tab
    wxStaticText *firstHeader = new wxStaticText(this->notebook, wxID_ANY, "WELCOME ADMIN!");
    firstHeader->SetForegroundColour(Settings::getInstance().colors.textPrimary);
    this->notebook->AddPage(firstHeader, L"Home");

    // Profile Tab
    wxPanel *profilePanel = new wxPanel(this->notebook);
    wxStaticText *secondHeader = new wxStaticText(profilePanel, wxID_ANY, "WELCOME ADMIN!");
    secondHeader->SetForegroundColour(Settings::getInstance().colors.textPrimary);
    this->notebook->AddPage(profilePanel, L"Profile");

    // Add to Main Sizer
    sizer->Add(new wxStaticText(this, wxID_ANY, "WELCOME ADMIN!"), 0, wxEXPAND | wxALL, 20);
    sizer->Add(this->notebook, 1, wxEXPAND | wxALL);
}

/* ---------------- Doctor Dashboard ---------------- */
DoctorDashboard::DoctorDashboard(wxPanel *parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(200, 100))
{
    this->parent = parent;
    buildUI();
}
void DoctorDashboard::buildUI()
{
    std::cout << "Started\n";
    this->notebook = new wxNotebook(this, wxID_ANY);

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(sizer);

    // Welcome Text
    wxStaticText *firstHeader = new wxStaticText(this->notebook, wxID_ANY, "WELCOME ADMIN!");
    firstHeader->SetForegroundColour(Settings::getInstance().colors.textPrimary);
    this->notebook->AddPage(firstHeader, L"Home");

    wxStaticText *secondHeader = new wxStaticText(this->notebook, wxID_ANY, "WELCOME ADMIN!");
    secondHeader->SetForegroundColour(Settings::getInstance().colors.textPrimary);
    this->notebook->AddPage(secondHeader, L"Profile");
    sizer->Add(this->notebook, 1, wxEXPAND | wxALL);
}
/* ---------------- Psycologist Dashboard ---------------- */
PsychologistDashboard::PsychologistDashboard(wxPanel *parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(200, 100))
{
    this->parent = parent;
    buildUI();
}
void PsychologistDashboard::buildUI()
{
    std::cout << "Started\n";
    this->notebook = new wxNotebook(this, wxID_ANY);

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(sizer);

    // Welcome Text
    wxStaticText *firstHeader = new wxStaticText(this->notebook, wxID_ANY, "WELCOME ADMIN!");
    firstHeader->SetForegroundColour(Settings::getInstance().colors.textPrimary);
    this->notebook->AddPage(firstHeader, L"Home");

    wxStaticText *secondHeader = new wxStaticText(this->notebook, wxID_ANY, "WELCOME ADMIN!");
    secondHeader->SetForegroundColour(Settings::getInstance().colors.textPrimary);
    this->notebook->AddPage(secondHeader, L"Profile");
    sizer->Add(this->notebook, 1, wxEXPAND | wxALL);
}
/* ---------------- Dietitian Dashboard ---------------- */
DietitianDashboard::DietitianDashboard(wxPanel *parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(200, 100))
{
    this->parent = parent;
    buildUI();
}
void DietitianDashboard::buildUI()
{
    std::cout << "Started\n";
    this->notebook = new wxNotebook(this, wxID_ANY);

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(sizer);

    // Welcome Text
    wxStaticText *firstHeader = new wxStaticText(this->notebook, wxID_ANY, "WELCOME ADMIN!");
    firstHeader->SetForegroundColour(Settings::getInstance().colors.textPrimary);
    this->notebook->AddPage(firstHeader, L"Home");

    wxStaticText *secondHeader = new wxStaticText(this->notebook, wxID_ANY, "WELCOME ADMIN!");
    secondHeader->SetForegroundColour(Settings::getInstance().colors.textPrimary);
    this->notebook->AddPage(secondHeader, L"Profile");
    sizer->Add(this->notebook, 1, wxEXPAND | wxALL);
}
/* ---------------- Nurse Dashboard ---------------- */
NurseDashboard::NurseDashboard(wxPanel *parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(200, 100))
{
    this->parent = parent;
    buildUI();
}
void NurseDashboard::buildUI()
{
    std::cout << "Started\n";
    this->notebook = new wxNotebook(this, wxID_ANY);

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(sizer);

    // Welcome Text
    wxStaticText *firstHeader = new wxStaticText(this->notebook, wxID_ANY, "WELCOME ADMIN!");
    firstHeader->SetForegroundColour(Settings::getInstance().colors.textPrimary);
    this->notebook->AddPage(firstHeader, L"Home");

    wxStaticText *secondHeader = new wxStaticText(this->notebook, wxID_ANY, "WELCOME ADMIN!");
    secondHeader->SetForegroundColour(Settings::getInstance().colors.textPrimary);
    this->notebook->AddPage(secondHeader, L"Profile");
    sizer->Add(this->notebook, 1, wxEXPAND | wxALL);
}
/* ---------------- Receptionist Dashboard ---------------- */
ReceptionistDashboard::ReceptionistDashboard(wxPanel *parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(200, 100))
{
    this->parent = parent;
    buildUI();
}
void ReceptionistDashboard::buildUI()
{
    std::cout << "Started\n";
    this->notebook = new wxNotebook(this, wxID_ANY);

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(sizer);

    // Welcome Text
    wxStaticText *firstHeader = new wxStaticText(this->notebook, wxID_ANY, "WELCOME ADMIN!");
    firstHeader->SetForegroundColour(Settings::getInstance().colors.textPrimary);
    this->notebook->AddPage(firstHeader, L"Home");

    wxStaticText *secondHeader = new wxStaticText(this->notebook, wxID_ANY, "WELCOME ADMIN!");
    secondHeader->SetForegroundColour(Settings::getInstance().colors.textPrimary);
    this->notebook->AddPage(secondHeader, L"Profile");
    sizer->Add(this->notebook, 1, wxEXPAND | wxALL);
}
/* ---------------- Patient Dashboard ---------------- */
PatientDashboard::PatientDashboard(wxPanel *parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(200, 100))
{
    this->parent = parent;
    buildUI();
}
void PatientDashboard::buildUI()
{
    std::cout << "Started\n";
    this->notebook = new wxNotebook(this, wxID_ANY);

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(sizer);

    // Welcome Text
    wxStaticText *firstHeader = new wxStaticText(this->notebook, wxID_ANY, "WELCOME ADMIN!");
    firstHeader->SetForegroundColour(Settings::getInstance().colors.textPrimary);
    this->notebook->AddPage(firstHeader, L"Home");

    wxStaticText *secondHeader = new wxStaticText(this->notebook, wxID_ANY, "WELCOME ADMIN!");
    secondHeader->SetForegroundColour(Settings::getInstance().colors.textPrimary);
    this->notebook->AddPage(secondHeader, L"Profile");
    sizer->Add(this->notebook, 1, wxEXPAND | wxALL);
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
    wxBoxSizer *footerSizer = new wxBoxSizer(wxHORIZONTAL);
    this->logoutBtn = new wxButton(this, wxID_OK, "Logout");
    this->logoutBtn->SetBackgroundColour(Settings::getInstance().colors.error);
    this->logoutBtn->Bind(wxEVT_BUTTON, &Footer::onLogout, this);

    footerSizer->Add(new wxStaticText(this, wxID_ANY, "© 2025 MWMS"), 0, wxALL, 5);
    footerSizer->AddStretchSpacer(); // Pushes the button to the right
    footerSizer->Add(this->logoutBtn, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
    this->SetSizer(footerSizer);
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
