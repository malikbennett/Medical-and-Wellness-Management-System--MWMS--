#include <BookAppointmentDialog.h>
#include <UserManager.h>
#include <Helper.h>

BookAppointmentDialog::BookAppointmentDialog(wxWindow *parent)
    : wxDialog(parent, wxID_ANY, "Book Appointment", wxDefaultPosition, wxSize(240, 360))
{
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    // Gets all doctors
    vector<User *> users = UserManager::getAllUsers(2);
    wxArrayString doctors;
    for (auto &user : users)
    {
        doctors.Add("Dr." + trimString(user->getProfileRecords()[4]) + "(" + trimString(user->getProfileRecords()[1]) + ")");
    }
    doctorNumberCtrl = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, doctors);
    dateCtrl = new wxDatePickerCtrl(this, wxID_ANY);
    wxArrayString times;
    times.Add("09:00 AM");
    times.Add("10:00 AM");
    times.Add("11:00 AM");
    times.Add("01:00 PM");
    times.Add("02:00 PM");
    timeSlotCtrl = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, times);

    sizer->Add(new wxStaticText(this, wxID_ANY, "Doctor Number:"), 0, wxALL, 5);
    sizer->Add(doctorNumberCtrl, 0, wxTOP | wxEXPAND, 20);

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

int BookAppointmentDialog::GetDoctorNumber() const
{
    string choice = this->doctorNumberCtrl->GetStringSelection().ToStdString();

    size_t start = choice.find('(');
    size_t end = choice.find(')');

    if (start != string::npos && end != string::npos && end > start)
    {
        string numberStr = choice.substr(start + 1, end - start - 1);
        return stoi(numberStr);
    }
    return 0;
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
    if (!doctorNumberCtrl->GetSelection() || !timeSlotCtrl->GetSelection())
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
