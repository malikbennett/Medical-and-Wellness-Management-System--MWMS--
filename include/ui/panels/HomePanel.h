#pragma once

#include <wx/wx.h>
#include <wx/notebook.h>

#include <Dashboard.h>

// Classes that displays the role-based dashboard panels/screens
/* ---------------- Menu ---------------- */
class Menu : public wxPanel
{
public:
    Menu(wxPanel *parent);
    void buildUI();

private:
    wxPanel *parent;
};


/* ---------------- Footer ---------------- */
enum class FooterState { LOGIN, SIGNUP, DASHBOARD };

class Footer : public wxPanel
{
public:
    Footer(wxPanel *parent);
    void buildUI();
    wxButton* GetActionButton();
    void updateForDashboard();
    void SetState(FooterState state);

private:
    wxPanel *parent;
    wxStaticText *infoText;
    wxButton *actionBtn;
    void updateForSignup(wxCommandEvent &event);
    void updateForLogin(wxCommandEvent &event);
    void onLogout(wxCommandEvent &event);
};
