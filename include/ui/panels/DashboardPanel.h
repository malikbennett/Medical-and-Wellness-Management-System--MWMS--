#pragma once

#include <wx/wx.h>
#include <wx/notebook.h>

// Classes that displays the role-based dashboard panels/screens
/* ---------------- Admin Dashboard ---------------- */
class AdminDashboard : public wxPanel
{
public:
    AdminDashboard(wxPanel *parent);
    void buildUI();
private:
    wxPanel *parent;
    wxNotebook *notebook;
};
/* ---------------- Doctor Dashboard ---------------- */
class DoctorDashboard : public wxPanel
{
public:
    DoctorDashboard(wxPanel *parent);
    void buildUI();
private:
    wxPanel *parent;
    wxNotebook *notebook;
};
/* ---------------- Psycologist Dashboard ---------------- */
class PsychologistDashboard : public wxPanel
{
public:
    PsychologistDashboard(wxPanel *parent);
    void buildUI();
private:
    wxPanel *parent;
    wxNotebook *notebook;
};
/* ---------------- Dietitian Dashboard ---------------- */
class DietitianDashboard : public wxPanel
{
public:
    DietitianDashboard(wxPanel *parent);
    void buildUI();
private:
    wxPanel *parent;
    wxNotebook *notebook;
};
/* ---------------- Nurse Dashboard ---------------- */
class NurseDashboard : public wxPanel
{
public:
    NurseDashboard(wxPanel *parent);
    void buildUI();
private:
    wxPanel *parent;
    wxNotebook *notebook;
};
/* ---------------- Receptionist Dashboard ---------------- */
class ReceptionistDashboard : public wxPanel
{
public:
    ReceptionistDashboard(wxPanel *parent);
    void buildUI();
private:
    wxPanel *parent;
    wxNotebook *notebook;
};
/* ---------------- Patient Dashboard ---------------- */
class PatientDashboard : public wxPanel
{
public:
    PatientDashboard(wxPanel *parent);
    void buildUI();
private:
    wxPanel *parent;
    wxNotebook *notebook;
};
/* ---------------- Footer Dashboard ---------------- */
class Footer : public wxPanel
{
public:
    Footer(wxPanel *parent);
    void onLogout(wxCommandEvent &event);
    void buildUI();

private:
    wxPanel *parent;
    wxButton* logoutBtn;
};
