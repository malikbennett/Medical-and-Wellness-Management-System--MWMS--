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
    notebook->AddPage(createMyPatientsTab(), "Patients");
    notebook->AddPage(createAppointmentsTab(), "Appointments");
    notebook->AddPage(createDietPlansTab(), "DietPlans");
    notebook->AddPage(createNutritionHistoryTab(), "Nutrition History");
    // Add to Main Sizer
    sizer->Add(this->notebook, 1, wxEXPAND | wxALL);
}
wxPanel *DietitianDashboard::createDietPlansTab() {
    wxPanel *panel = new wxPanel(notebook);
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    panel->SetSizer(sizer);
    return panel;
};
wxPanel *DietitianDashboard::createNutritionHistoryTab() {
    wxPanel *panel = new wxPanel(notebook);
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    panel->SetSizer(sizer);
    return panel;
};
