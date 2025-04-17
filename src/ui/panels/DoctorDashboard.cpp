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
    notebook->AddPage(createMyPatientsTab(), "My Patients");
    notebook->AddPage(createAppointmentsTab(), "Appointments");
    notebook->AddPage(createReferralsTab(), "Referrals");
    notebook->AddPage(createPrescriptionsTab(), "Prescriptions");

    // Add to Main Sizer
    sizer->Add(this->notebook, 1, wxEXPAND | wxALL);
}
    wxPanel* DoctorDashboard::createMyPatientsTab(){
    wxPanel *panel = new wxPanel(notebook);
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    panel->SetSizer(sizer);
    return panel;
    };
    wxPanel* DoctorDashboard::createAppointmentsTab(){
    wxPanel *panel = new wxPanel(notebook);
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    panel->SetSizer(sizer);
    return panel;
    };
    wxPanel* DoctorDashboard::createReferralsTab(){
    wxPanel *panel = new wxPanel(notebook);
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    panel->SetSizer(sizer);
    return panel;
    };
    wxPanel* DoctorDashboard::createPrescriptionsTab(){
    wxPanel *panel = new wxPanel(notebook);
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    panel->SetSizer(sizer);
    return panel;
    };
