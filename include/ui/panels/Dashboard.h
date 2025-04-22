#pragma once

#include <wx/wx.h>
#include <wx/notebook.h>
#include <ListViewCtrl.h>

/* ---------------- Base Dashboard ---------------- */
class Dashboard : public wxPanel
{
public:
    Dashboard(wxPanel *parent);
    virtual void buildUI() = 0;
    wxPanel *createHomeTab();
    wxPanel *createManageStaffTab();
    wxPanel *createManagePatientsTab();
    wxPanel *createPrescriptionsTab();
    wxPanel *createAppointmentsTab();
    wxPanel *createReportsTab();
    wxPanel *createReferralsTab();
private:
    wxPanel *parent;
    ListView *list;

    void OnBookAppointment(wxCommandEvent &event);

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
    wxPanel *createReportsTab();
};
/* ---------------- Dietitian Dashboard ---------------- */
class DietitianDashboard : public Dashboard
{
public:
    DietitianDashboard(wxPanel *parent);
    void buildUI() override;
    wxPanel* createDietPlansTab();
    wxPanel* createNutritionHistoryTab();
};
/* ---------------- Doctor Dashboard ---------------- */
class DoctorDashboard : public Dashboard
{
public:
    DoctorDashboard(wxPanel *parent);
    void buildUI() override;
    wxPanel* createReferralsTab();
};
/* ---------------- Nurse Dashboard ---------------- */
class NurseDashboard : public Dashboard
{
public:
    NurseDashboard(wxPanel *parent);
    void buildUI() override;
    wxPanel* createPatientInfoTab();

};
/* ---------------- Patient Dashboard ---------------- */
class PatientDashboard : public Dashboard
{
public:
    PatientDashboard(wxPanel *parent);
    void buildUI() override;
    wxPanel* createMedicalHistoryTab();

};
/* ---------------- Psycologist Dashboard ---------------- */
class PsychologistDashboard : public Dashboard
{
public:
    PsychologistDashboard(wxPanel *parent);
    void buildUI() override;
    wxPanel* createSessionNotesTab();
    wxPanel* createReferralsTab();

};
/* ---------------- Receptionist Dashboard ---------------- */
class ReceptionistDashboard : public Dashboard
{
public:
    ReceptionistDashboard(wxPanel *parent);
    void buildUI() override;
    wxPanel* createVisitorLogTab();
};
