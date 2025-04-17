#include <Dashboard.h>
#include <Helper.h>
#include <Session.h>
#include <Employee.h>
#include <Patient.h>

Dashboard::Dashboard(wxPanel* parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize){
    this->parent = parent;
    this->headingFont = wxFont(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    this->paraFont = wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
}

wxPanel* Dashboard::createHomeTab()
{
    const User *user = Session::GetCurrentUser();
    const Employee *emp = dynamic_cast<const Employee *>(user);
    const Patient *pat = dynamic_cast<const Patient *>(user);

    wxPanel* panel = new wxPanel(notebook);
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    AddText(panel,sizer,"Overview:",this->headingFont), 5;
    AddText(panel,sizer,"Nothing to see here",this->paraFont, 5);
    panel->SetSizer(sizer);
    return panel;
}
