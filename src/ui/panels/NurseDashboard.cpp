
#include <Dashboard.h>
#include <Settings.h>
#include <Helper.h>

/* ---------------- Nurse Dashboard ---------------- */
NurseDashboard::NurseDashboard(wxPanel *parent) : Dashboard(parent) { buildUI(); }
void NurseDashboard::buildUI()
{
    this->notebook = new wxNotebook(this, wxID_ANY);

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(sizer);

    notebook->AddPage(createHomeTab(), "Home");
    notebook->AddPage(createPatientInfoTab(), "Manage Patients");
    notebook->AddPage(createAppointmentsTab(), "Appointments");
    notebook->AddPage(createMedicationsTab(), "Medications");

    // Add to Main Sizer
    sizer->Add(this->notebook, 1, wxEXPAND | wxALL);
}
wxPanel *NurseDashboard::createPatientInfoTab()
{
    wxPanel *panel = new wxPanel(notebook);
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    panel->SetSizer(sizer);
    return panel;
};
wxPanel *NurseDashboard::createAppointmentsTab()
{
    wxPanel *panel = new wxPanel(notebook);
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    panel->SetSizer(sizer);
    return panel;
};
wxPanel *NurseDashboard::createMedicationsTab()
{
    wxPanel *panel = new wxPanel(notebook);
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    panel->SetSizer(sizer);
    return panel;
};
