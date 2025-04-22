#include <Dashboard.h>
#include <Helper.h>
#include <Settings.h>
#include <UserManager.h>
#include <ListViewCtrl.h>

/* ---------------- Admin Dashboard ---------------- */
AdminDashboard::AdminDashboard(wxPanel *parent) : Dashboard(parent) { buildUI(); }
void AdminDashboard::buildUI()
{
    std::cout << "Started\n";
    this->notebook = new wxNotebook(this, wxID_ANY);

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(sizer);

    notebook->AddPage(createHomeTab(), "Home");
    notebook->AddPage(createManageStaffTab(), "Manage Staff");
    notebook->AddPage(createManagePatientsTab(), "Manage Patients");
    notebook->AddPage(createAppointmentsTab(), "Appointments");
    notebook->AddPage(createReportsTab(), "Reports");

    // Add to Main Sizer
    sizer->Add(this->notebook, 1, wxEXPAND | wxALL);
}

/* ---------------- Tab Panels ---------------- */
wxPanel *AdminDashboard::createManageStaffTab()
{
    wxPanel *panel = new wxPanel(notebook);
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    // Header
    wxPanel *headerPanel = new wxPanel(panel);
    wxBoxSizer *headerSizer = new wxBoxSizer(wxHORIZONTAL);
    AddText(headerPanel, headerSizer, "Employee Records:", this->headingFont, 10);

    // Body
    wxPanel *bodyPanel = new wxPanel(panel);
    wxBoxSizer *bodySizer = new wxBoxSizer(wxVERTICAL);
    bodyPanel->SetBackgroundColour(Settings::getInstance().colors.surface);

    ListView *records = new ListView(bodyPanel,wxID_ANY,wxDefaultPosition,wxDefaultSize);
    records->loadEmployeeFields();
    records->RefreshAfterUpdate();

    bodySizer->Add(records, 1, wxEXPAND);

    sizer->Add(headerPanel, 0, wxEXPAND);
    sizer->Add(bodyPanel, 1, wxEXPAND);

    bodyPanel->SetSizer(bodySizer);
    headerPanel->SetSizer(headerSizer);
    panel->SetSizer(sizer);
    return panel;
}

wxPanel *AdminDashboard::createReportsTab()
{
    wxPanel *panel = new wxPanel(notebook);
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    AddText(panel, sizer, "Reports & Logs:", this->headingFont, 10);
    AddText(panel, sizer, "Work in progress...", this->paraFont, 10);

    panel->SetSizer(sizer);
    return panel;
}
