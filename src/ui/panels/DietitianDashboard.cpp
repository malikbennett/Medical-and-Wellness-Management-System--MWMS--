#include <Dashboard.h>
#include <Settings.h>
#include <Helper.h>

/* ---------------- Dietitian Dashboard ---------------- */
DietitianDashboard::DietitianDashboard(wxPanel *parent) : Dashboard(parent) { buildUI(); }
void DietitianDashboard::buildUI()
{
    this->notebook = new wxNotebook(this, wxID_ANY);

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(sizer);

    notebook->AddPage(createHomeTab(), "Home");
    notebook->AddPage(createAppointmentsTab(), "Appointments");
    notebook->AddPage(createPrescriptionsTab(), "Prescriptions");
    notebook->AddPage(createDietPlansTab(), "DietPlans");
    notebook->AddPage(createNutritionHistoryTab(), "Nutrition History");
    // Add to Main Sizer
    sizer->Add(this->notebook, 1, wxEXPAND | wxALL);
}
wxPanel *DietitianDashboard::createDietPlansTab() {
    wxPanel *panel = new wxPanel(notebook);
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    AddText(panel, sizer, "Diet Plans:", this->headingFont, 10);
    AddText(panel, sizer, "Work in progress...", this->paraFont, 10);
    panel->SetSizer(sizer);
    return panel;
};
wxPanel *DietitianDashboard::createNutritionHistoryTab() {
    wxPanel *panel = new wxPanel(notebook);
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    AddText(panel, sizer, "Nutrition History:", this->headingFont, 10);
    AddText(panel, sizer, "Work in progress...", this->paraFont, 10);
    panel->SetSizer(sizer);
    return panel;
};
