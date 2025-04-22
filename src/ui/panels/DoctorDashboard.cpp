#include <Dashboard.h>
#include <Settings.h>
#include <Helper.h>

/* ---------------- Doctor Dashboard ---------------- */
DoctorDashboard::DoctorDashboard(wxPanel *parent) : Dashboard(parent){buildUI();}
void DoctorDashboard::buildUI()
{
    this->notebook = new wxNotebook(this, wxID_ANY);

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(sizer);

    notebook->AddPage(createHomeTab(), "Home");
    notebook->AddPage(createAppointmentsTab(), "Appointments");
    notebook->AddPage(createPrescriptionsTab(), "Prescriptions");
    notebook->AddPage(createReferralsTab(), "Referrals");

    // Add to Main Sizer
    sizer->Add(this->notebook, 1, wxEXPAND | wxALL);
};
wxPanel *DoctorDashboard::createReferralsTab()
{
    wxPanel *panel = new wxPanel(notebook);
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    AddText(panel, sizer, "Referrals:", this->headingFont, 10);
    AddText(panel, sizer, "Work in progress.....", this->paraFont, 10);
    panel->SetSizer(sizer);
    return panel;
};
