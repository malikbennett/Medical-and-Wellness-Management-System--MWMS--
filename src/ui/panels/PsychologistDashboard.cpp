#include <Dashboard.h>
#include <Settings.h>

/* ---------------- Psycologist Dashboard ---------------- */
PsychologistDashboard::PsychologistDashboard(wxPanel *parent) : Dashboard(parent) { buildUI(); }
void PsychologistDashboard::buildUI()
{
    this->notebook = new wxNotebook(this, wxID_ANY);

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(sizer);

    notebook->AddPage(createHomeTab(), "Home");
    notebook->AddPage(createMyPatientsTab(), "My Patients");
    notebook->AddPage(createAppointmentsTab(), "Appointments");
    notebook->AddPage(createSessionNotesTab(), "Session Notes");
    notebook->AddPage(createReferralsTab(), "Referrals");

    // Add to Main Sizer
    sizer->Add(this->notebook, 1, wxEXPAND | wxALL);
}
wxPanel *PsychologistDashboard::createMyPatientsTab()
{
    wxPanel *panel = new wxPanel(notebook);
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    panel->SetSizer(sizer);
    return panel;
};
wxPanel *PsychologistDashboard::createAppointmentsTab()
{
    wxPanel *panel = new wxPanel(notebook);
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    panel->SetSizer(sizer);
    return panel;
};
wxPanel *PsychologistDashboard::createSessionNotesTab()
{
    wxPanel *panel = new wxPanel(notebook);
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    panel->SetSizer(sizer);
    return panel;
};
wxPanel *PsychologistDashboard::createReferralsTab()
{
    wxPanel *panel = new wxPanel(notebook);
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    panel->SetSizer(sizer);
    return panel;
};
