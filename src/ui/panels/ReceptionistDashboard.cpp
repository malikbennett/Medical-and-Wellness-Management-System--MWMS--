#include <Dashboard.h>
#include <Settings.h>
#include <Helper.h>

/* ---------------- Receptionist Dashboard ---------------- */
ReceptionistDashboard::ReceptionistDashboard(wxPanel *parent) : Dashboard(parent) { buildUI(); }
void ReceptionistDashboard::buildUI()
{
    this->notebook = new wxNotebook(this, wxID_ANY);

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(sizer);

    notebook->AddPage(createHomeTab(), "Home");
    notebook->AddPage(createAppointmentsTab(), "Appointments");
    notebook->AddPage(createVisitorLogTab(), "Visitor Log");

    // Add to Main Sizer
    sizer->Add(this->notebook, 1, wxEXPAND | wxALL);
}
wxPanel *ReceptionistDashboard::createVisitorLogTab()
{
    wxPanel *panel = new wxPanel(notebook);
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    AddText(panel, sizer, "Visitor Log:", this->headingFont, 10);
    AddText(panel, sizer, "Work in progress...", this->paraFont, 10);
    panel->SetSizer(sizer);
    return panel;
};
