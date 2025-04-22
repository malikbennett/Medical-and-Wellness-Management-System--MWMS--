#include <EditRecordPanel.h>
#include <ActionDialog.h>
#include <Helper.h>

ActionDialog::ActionDialog(wxPanel *parent, Appointment *apt, User *user, Prescription* pres)
    : wxDialog(parent, wxID_ANY, "Select Action", wxDefaultPosition, wxSize(400, 300)), apt(apt), user(user)
{
    sizer = new wxBoxSizer(wxVERTICAL);

    // Create and hide both panels
    if(apt != nullptr){
        editPanel = new EditRecordPanel(this,apt,EDIT_APPOINTMENT);
        removePanel = new wxPanel(this);
    }else if(user != nullptr){
        editPanel = new EditRecordPanel(this,user,EDIT_USER);
        removePanel = new wxPanel(this);
    }else if(pres != nullptr){
        editPanel = new EditRecordPanel(this,pres,EDIT_PRESCRIPTION);
        removePanel = new wxPanel(this);
    }

    // Build Remove Panel
    wxBoxSizer *removeSizer = new wxBoxSizer(wxVERTICAL);
    removeSizer->Add(new wxStaticText(removePanel, wxID_ANY, "Are you sure you want to delete?"), 0, wxALL, 5);
    // Add your delete logic/button
    removePanel->SetSizer(removeSizer);
    removePanel->Hide();

    sizer->Add(editPanel, 1, wxEXPAND);
    sizer->Add(removePanel, 1, wxEXPAND);

    // Buttons to switch views
    wxBoxSizer *btnSizer = new wxBoxSizer(wxHORIZONTAL);
    wxButton *editBtn = new wxButton(this, wxID_ANY, "Edit");
    wxButton *removeBtn = new wxButton(this, wxID_ANY, "Remove");
    btnSizer->Add(editBtn, 0, wxALL, 5);
    btnSizer->Add(removeBtn, 0, wxALL, 5);

    sizer->Add(btnSizer, 0, wxALIGN_CENTER);

    editBtn->Bind(wxEVT_BUTTON, &ActionDialog::OnShowEdit, this);
    removeBtn->Bind(wxEVT_BUTTON, &ActionDialog::OnShowRemove, this);

    SetSizerAndFit(sizer);
}

void ActionDialog::OnShowEdit(wxCommandEvent &)
{
    removePanel->Hide();
    editPanel->Show();
    editPanel->Layout();
    editPanel->Fit();
    Layout();
    Fit();
}

void ActionDialog::OnShowRemove(wxCommandEvent &)
{
    editPanel->Hide();
    removePanel->Show();
    Layout();
    Fit();
}
