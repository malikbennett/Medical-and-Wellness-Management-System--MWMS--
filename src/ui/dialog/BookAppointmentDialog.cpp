#include <BookAppointmentDialog.h>
#include <UserManager.h>
#include <Helper.h>

BookAppointmentDialog::BookAppointmentDialog(wxWindow *parent)
    : wxDialog(parent, wxID_ANY, "Book Appointment", wxDefaultPosition, wxSize(320, 400))
{
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    if (Session::GetCurrentUser()->getRole().roleLevel != "PATIENT")
    {
        vector<User *> users = UserManager::getAllUsers(7);
        wxArrayString patients;
        for (auto &user : users)
        {
            wxString name = trimString(user->getProfileRecords()[4]);
            wxString id = trimString(user->getProfileRecords()[1]);
            wxString title;
            if(user->getProfileRecords()[8] == "M")
                title = "Mr. ";
            else
                title = "Ms. ";
            patients.Add(title + name + "(" + id + ")");
        }
        patientNumberCtrl = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, patients);
        sizer->Add(new wxStaticText(this, wxID_ANY, "Patient Number:"), 0, wxALL, 5);
        sizer->Add(patientNumberCtrl, 0, wxTOP | wxEXPAND, 20);
    }

    // Gets all Medical Proffessionals
    vector<User *> users;
    wxArrayString medProf;

    auto addProfessionals = [&](int roleLevel, const wxString& title) {
        users = UserManager::getAllUsers(roleLevel);
        for (auto &user : users)
        {
            wxString name = trimString(user->getProfileRecords()[4]);
            wxString id = trimString(user->getProfileRecords()[1]);
            medProf.Add(title + " " + name + " (" + id + ")");
        }
        users.clear();
    };

    addProfessionals(2, "Dr.");
    addProfessionals(3, "Psych.");
    addProfessionals(4, "Diet.");

    medProfNumberCtrl = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, medProf);

    dateCtrl = new wxDatePickerCtrl(this, wxID_ANY);
    wxArrayString times;
    times.Add("09:00 AM");
    times.Add("10:00 AM");
    times.Add("11:00 AM");
    times.Add("01:00 PM");
    times.Add("02:00 PM");
    timeSlotCtrl = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, times);

    sizer->Add(new wxStaticText(this, wxID_ANY, "Medical Prof. Number:"), 0, wxALL, 5);
    sizer->Add(medProfNumberCtrl, 0, wxTOP | wxEXPAND, 20);

    sizer->Add(new wxStaticText(this, wxID_ANY, "Date:"), 0, wxALL, 5);
    sizer->Add(dateCtrl, 0, wxALL | wxEXPAND, 5);

    sizer->Add(new wxStaticText(this, wxID_ANY, "Time Slot:"), 0, wxALL, 5);
    sizer->Add(timeSlotCtrl, 0, wxALL | wxEXPAND, 5);

    wxButton *submitButton = new wxButton(this, wxID_OK, "Book");
    sizer->Add(submitButton, 0, wxTop | wxALIGN_CENTER , 20);

    submitButton->Bind(wxEVT_BUTTON, &BookAppointmentDialog::OnSubmit, this);

    Bind(wxEVT_CLOSE_WINDOW, &BookAppointmentDialog::OnClose, this);
    SetSizer(sizer);
}

int BookAppointmentDialog::GetNumber(wxChoice* Ctrl)
{
    string choice = Ctrl->GetStringSelection().ToStdString();

    size_t start = choice.find('(');
    size_t end = choice.find(')');

    if (start != string::npos && end != string::npos && end > start)
    {
        string numberStr = choice.substr(start + 1, end - start - 1);
        return stoi(numberStr);
    }
    return 0;
}

wxChoice *BookAppointmentDialog::GetPatientCtrl() const{
    return this->patientNumberCtrl;
}

wxChoice *BookAppointmentDialog::GetMedProfCtrl() const{
    return this->medProfNumberCtrl;
}

wxDateTime BookAppointmentDialog::GetDate() const
{
    return dateCtrl->GetValue();
}

wxString BookAppointmentDialog::GetTimeSlot() const
{
    return timeSlotCtrl->GetStringSelection();
}

void BookAppointmentDialog::OnSubmit(wxCommandEvent &event)
{
    int medProfIndex = medProfNumberCtrl->GetSelection();
    int timeSlotIndex = timeSlotCtrl->GetSelection();

    if (medProfIndex != wxNOT_FOUND && timeSlotIndex != wxNOT_FOUND)
    {
        EndModal(wxID_OK);
    }
    else
    {
        wxMessageBox("Please fill all fields.");
    }
}

void BookAppointmentDialog::OnClose(wxCloseEvent& event)
{
    EndModal(wxID_CANCEL);
}
