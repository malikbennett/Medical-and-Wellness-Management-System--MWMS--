#include <Dashboard.h>
#include <Settings.h>
#include <Helper.h>

/* ---------------- Psycologist Dashboard ---------------- */
PsychologistDashboard::PsychologistDashboard(wxPanel *parent) : Dashboard(parent) { buildUI(); }
void PsychologistDashboard::buildUI()
{
    this->notebook = new wxNotebook(this, wxID_ANY);

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(sizer);

    notebook->AddPage(createHomeTab(), "Home");
    notebook->AddPage(createAppointmentsTab(), "Appointments");
    notebook->AddPage(createPrescriptionsTab(), "Prescriptions");
    notebook->AddPage(createSessionNotesTab(), "Session Notes");
    notebook->AddPage(createReferralsTab(), "Referrals");

    // Add to Main Sizer
    sizer->Add(this->notebook, 1, wxEXPAND | wxALL);
}
wxPanel *PsychologistDashboard::createSessionNotesTab()
{
    wxPanel *panel = new wxPanel(notebook);
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    AddText(panel, sizer, "Session Notes:", this->headingFont, 10);
    AddText(panel, sizer, "Work in progress...", this->paraFont, 10);

    panel->SetSizer(sizer);
    return panel;
};
wxPanel *PsychologistDashboard::createReferralsTab()
{
    wxPanel *panel = new wxPanel(notebook);
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    AddText(panel, sizer, "Referrals:", this->headingFont, 10);
    AddText(panel, sizer, "Work in progress...", this->paraFont, 10);

    panel->SetSizer(sizer);
    return panel;
};
