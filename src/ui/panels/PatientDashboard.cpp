#include <Dashboard.h>
#include <Settings.h>
#include <Helper.h>

/* ---------------- Patient Dashboard ---------------- */
PatientDashboard::PatientDashboard(wxPanel *parent) : Dashboard(parent) { buildUI(); }
void PatientDashboard::buildUI()
{
    this->notebook = new wxNotebook(this, wxID_ANY);

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(sizer);

    notebook->AddPage(createHomeTab(), "Home");
    notebook->AddPage(createAppointmentsTab(), "Appointments");
    notebook->AddPage(createMedicalHistoryTab(), "Medical History");

    // Add to Main Sizer
    sizer->Add(this->notebook, 1, wxEXPAND | wxALL);
}
wxPanel *PatientDashboard::createMedicalHistoryTab()
{
    wxPanel *panel = new wxPanel(notebook);
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    AddText(panel, sizer, "Medication History:", this->headingFont, 10);
    AddText(panel, sizer, "Work in progress.....", this->paraFont, 10);

    panel->SetSizer(sizer);
    return panel;
};
