#include <RemoveRecordDialog.h>
#include <Helper.h>

RemoveRecordDialog::RemoveRecordDialog(wxPanel *parent, User *user)
    : wxDialog(parent, wxID_ANY, "Remove Record", wxDefaultPosition, wxSize(300, 300))
{
    this->user = user;

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    // dateCtrl = new wxTextCtrl(this, wxID_ANY, Date::toString(emp->getAppointmentDate()));
    // timeCtrl = new wxTextCtrl(this, wxID_ANY, emp->getAppointmentTime());
    statusChoice = new wxChoice(this, wxID_ANY);
    statusChoice->Append("Scheduled");
    statusChoice->Append("Completed");
    statusChoice->Append("Cancelled");
    // statusChoice->SetStringSelection(statusToString(emp->getStatus()));

    sizer->Add(new wxStaticText(this, wxID_ANY, "Date:"), 0, wxALL, 5);
    // sizer->Add(dateCtrl, 0, wxALL | wxEXPAND, 5);
    sizer->Add(new wxStaticText(this, wxID_ANY, "Time:"), 0, wxALL, 5);
    // sizer->Add(timeCtrl, 0, wxALL | wxEXPAND, 5);
    sizer->Add(new wxStaticText(this, wxID_ANY, "Status:"), 0, wxALL, 5);
    sizer->Add(statusChoice, 0, wxALL | wxEXPAND, 5);

    sizer->Add(CreateButtonSizer(wxOK | wxCANCEL), 0, wxALL | wxALIGN_CENTER, 10);
    SetSizer(sizer);
}

RemoveRecordDialog::RemoveRecordDialog(wxPanel *parent, Appointment *apt)
    : wxDialog(parent, wxID_ANY, "Add Record", wxDefaultPosition, wxSize(300, 300))
{
    this->apt = apt;

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    // dateCtrl = new wxTextCtrl(this, wxID_ANY, Date::toString(emp->getAppointmentDate()));
    // timeCtrl = new wxTextCtrl(this, wxID_ANY, emp->getAppointmentTime());
    statusChoice = new wxChoice(this, wxID_ANY);
    statusChoice->Append("Scheduled");
    statusChoice->Append("Completed");
    statusChoice->Append("Cancelled");
    // statusChoice->SetStringSelection(statusToString(emp->getStatus()));

    sizer->Add(new wxStaticText(this, wxID_ANY, "Date:"), 0, wxALL, 5);
    // sizer->Add(dateCtrl, 0, wxALL | wxEXPAND, 5);
    sizer->Add(new wxStaticText(this, wxID_ANY, "Time:"), 0, wxALL, 5);
    // sizer->Add(timeCtrl, 0, wxALL | wxEXPAND, 5);
    sizer->Add(new wxStaticText(this, wxID_ANY, "Status:"), 0, wxALL, 5);
    sizer->Add(statusChoice, 0, wxALL | wxEXPAND, 5);

    sizer->Add(CreateButtonSizer(wxOK | wxCANCEL), 0, wxALL | wxALIGN_CENTER, 10);
    SetSizer(sizer);
}

void RemoveRecordDialog::EndModal(int retCode)
{
    if (retCode == wxID_OK)
    {
        // emp->setAppointmentDate(dateCtrl->GetValue().ToStdString());
        // emp->setAppointmentTime(timeCtrl->GetValue().ToStdString());
        // emp->setStatus(stringToStatus(statusChoice->GetStringSelection().ToStdString()));
        // emp->saveAppointment();
    }
    wxDialog::EndModal(retCode);
}
