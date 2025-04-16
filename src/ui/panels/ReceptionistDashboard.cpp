#include <Dashboard.h>
#include <Settings.h>

/* ---------------- Receptionist Dashboard ---------------- */
ReceptionistDashboard::ReceptionistDashboard(wxPanel *parent) : Dashboard(parent) { buildUI(); }
void ReceptionistDashboard::buildUI()
{
    this->notebook = new wxNotebook(this, wxID_ANY);

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(sizer);

    notebook->AddPage(createHomeTab(), "Home");
    notebook->AddPage(createPatientRegistryTab(), "Patient Registry");
    notebook->AddPage(createAppointmentsTab(), "Appointments");
    notebook->AddPage(createVisitorLogTab(), "Visitor Log");

    // Add to Main Sizer
    sizer->Add(this->notebook, 1, wxEXPAND | wxALL);
}
wxPanel *ReceptionistDashboard::createPatientRegistryTab()
{
    wxPanel *panel = new wxPanel(notebook);
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    panel->SetSizer(sizer);
    return panel;
};
wxPanel *ReceptionistDashboard::createAppointmentsTab()
{
    wxPanel *panel = new wxPanel(notebook);
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    panel->SetSizer(sizer);
    return panel;
};
wxPanel *ReceptionistDashboard::createVisitorLogTab()
{
    wxPanel *panel = new wxPanel(notebook);
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    panel->SetSizer(sizer);
    return panel;
};
