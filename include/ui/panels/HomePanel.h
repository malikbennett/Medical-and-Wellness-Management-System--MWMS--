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
