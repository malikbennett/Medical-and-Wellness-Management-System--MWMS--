#pragma once

#include <wx/wx.h>
#include <wx/notebook.h>
#include <GuiHealper.h>

/* ---------------- Base Dashboard ---------------- */
class Dashboard : public wxPanel
{
public:
    Dashboard(wxPanel *parent);
    virtual void buildUI() = 0;
    wxPanel *createHomeTab();
    wxPanel *createManageStaffTab();
    wxPanel *createManagePatientsTab();
    wxPanel *createAppointmentsTab();
    wxPanel *createMedicationsTab();
    wxPanel *createReportsTab();
    wxPanel* createMyPatientsTab();
    wxPanel* createReferralsTab();
    wxPanel* createPrescriptionsTab();

private:
    wxPanel *parent;

protected:
    wxNotebook *notebook;
    wxFont headingFont;
    wxFont paraFont;
};

/* ---------------- Derived Dashboard ---------------- */
/* ---------------- Admin Dashboard ---------------- */
class AdminDashboard : public Dashboard
{
public:
    AdminDashboard(wxPanel *parent);
    void buildUI() override;
    wxPanel *createManageStaffTab();
    wxPanel *createManagePatientsTab();
    wxPanel *createAppointmentsTab();
    wxPanel *createMedicationsTab();
    wxPanel *createReportsTab();
};
/* ---------------- Dietitian Dashboard ---------------- */
class DietitianDashboard : public Dashboard
{
public:
    DietitianDashboard(wxPanel *parent);
    void buildUI() override;
    wxPanel* createPatientsTab();
    wxPanel* createAppointmentsTab();
    wxPanel* createDietPlansTab();
    wxPanel* createNutritionHistoryTab();

};
/* ---------------- Doctor Dashboard ---------------- */
class DoctorDashboard : public Dashboard
{
public:
    DoctorDashboard(wxPanel *parent);
    void buildUI() override;
    wxPanel* createMyPatientsTab();
    wxPanel* createAppointmentsTab();
    wxPanel* createReferralsTab();
    wxPanel* createPrescriptionsTab();

};
/* ---------------- Nurse Dashboard ---------------- */
class NurseDashboard : public Dashboard
{
public:
    NurseDashboard(wxPanel *parent);
    void buildUI() override;
    wxPanel* createPatientInfoTab();
    wxPanel* createAppointmentsTab();
    wxPanel* createMedicationsTab();

};
/* ---------------- Patient Dashboard ---------------- */
class PatientDashboard : public Dashboard
{
public:
    PatientDashboard(wxPanel *parent);
    void buildUI() override;
    wxPanel* createAppointmentsTab();
    wxPanel* createMedicalHistoryTab();

};
/* ---------------- Psycologist Dashboard ---------------- */
class PsychologistDashboard : public Dashboard
{
public:
    PsychologistDashboard(wxPanel *parent);
    void buildUI() override;
    wxPanel* createMyPatientsTab();
    wxPanel* createAppointmentsTab();
    wxPanel* createSessionNotesTab();
    wxPanel* createReferralsTab();

};
/* ---------------- Receptionist Dashboard ---------------- */
class ReceptionistDashboard : public Dashboard
{
public:
    ReceptionistDashboard(wxPanel *parent);
    void buildUI() override;
    wxPanel* createPatientRegistryTab();
    wxPanel* createAppointmentsTab();
    wxPanel* createVisitorLogTab();
};
