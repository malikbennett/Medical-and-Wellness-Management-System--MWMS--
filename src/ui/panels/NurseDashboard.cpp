
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
    notebook->AddPage(createAppointmentsTab(), "Appointments");
    notebook->AddPage(createPrescriptionsTab(), "Prescriptions");

    // Add to Main Sizer
    sizer->Add(this->notebook, 1, wxEXPAND | wxALL);
}
