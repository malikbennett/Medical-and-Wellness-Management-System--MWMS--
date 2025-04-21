#include <EditRecordPanel.h>
#include <Employee.h>
#include <Patient.h>
#include <Status.h>
#include <Settings.h>
#include <Helper.h>
#include <sstream>

EditRecordPanel::EditRecordPanel(wxDialog *parent, User *user, EditMode mode)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(600, 450))
{
    this->mode = mode;
    this->user = user;

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    wxScrolledWindow *scrolledPanel = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL);
    scrolledPanel->SetScrollRate(5, 5);

    // Grid with 2 columns: Label | Input
    wxFlexGridSizer *formSizer = new wxFlexGridSizer(2, 10, 10); // 2 columns, 10px hgap, 10px vgap
    formSizer->AddGrowableCol(1, 1);                             // Make input column grow

    const Employee *emp = dynamic_cast<const Employee *>(Session::GetCurrentUser());
    const Patient *pat = dynamic_cast<const Patient *>(Session::GetCurrentUser());

    if (Session::GetCurrentUser()->getRole().roleLevel == "ADMIN")
    {
        // AddFormField(formSizer, scrolledPanel, "Username: ", userNameCtrl, user->getUsername());
        // AddFormField(formSizer, scrolledPanel, "Password:", passwordCtrl, user->getPassword());
        AddFormField(formSizer, scrolledPanel, "Role: ", roleCtrl, wxString::Format("%d", user->getRole().roleNumber));
        AddFormField(formSizer, scrolledPanel, "No. of Attempts:", noOfAttemptsCtrl, wxString::Format("%d", user->getAttemptsRemaining()));

        formSizer->Add(new wxStaticText(scrolledPanel, wxID_ANY, "Locked:"), 0, wxALL, 5);
        wxArrayString locked;
        locked.Add("yes");
        locked.Add("no");
        lockedChoice = new wxChoice(scrolledPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, locked);
        string isLocked = (user->locked() == true) ? "yes" : "no";
        DefaultChoice(lockedChoice, isLocked);
        formSizer->Add(lockedChoice, 0, wxALL | wxALIGN_LEFT, 5);
        if (this->user->getRole().roleLevel == "PATIENT")
        {
            AddFormField(formSizer, scrolledPanel, "First Name:", firstNameCtrl, user->getProfileRecords()[2]);
            AddFormField(formSizer, scrolledPanel, "Middle Name:", middleNameCtrl, user->getProfileRecords()[3]);
            AddFormField(formSizer, scrolledPanel, "Last Name:", lastNameCtrl, user->getProfileRecords()[4]);
            AddFormField(formSizer, scrolledPanel, "TRN:", TRN, user->getProfileRecords()[5]);

            wxDateTime dateStr;
            dateStr.ParseISODate(Date::toString(user->getProfileRecords()[6]));
            formSizer->Add(new wxStaticText(scrolledPanel, wxID_ANY, "DOB:"), 0, wxALL, 5);
            dobDateCtrl = new wxDatePickerCtrl(scrolledPanel, wxID_ANY,dateStr);
            formSizer->Add(dobDateCtrl, 1, wxEXPAND | wxALL, 5);

            dateStr.ParseISODate(Date::toString(user->getProfileRecords()[7]));
            formSizer->Add(new wxStaticText(scrolledPanel, wxID_ANY, "First Visit:"), 0, wxALL, 5);
            firstVisitDateCtrl = new wxDatePickerCtrl(scrolledPanel, wxID_ANY, dateStr);
            formSizer->Add(firstVisitDateCtrl, 0, wxALL | wxALIGN_LEFT, 5);

            formSizer->Add(new wxStaticText(scrolledPanel, wxID_ANY, "Gender:"), 0, wxALL, 5);
            wxArrayString gender;
            gender.Add("M");
            gender.Add("F");
            genderChoice = new wxChoice(scrolledPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, gender);
            DefaultChoice(genderChoice, trimString(user->getProfileRecords()[8]));
            formSizer->Add(genderChoice, 0, wxALL | wxALIGN_LEFT, 5);

            formSizer->Add(new wxStaticText(scrolledPanel, wxID_ANY, "Martial Status:"), 0, wxALL, 5);
            wxArrayString status;
            status.Add("Married");
            status.Add("Single");
            status.Add("Separated");
            status.Add("Divorced");
            status.Add("Other");
            martialStatusChoice = new wxChoice(scrolledPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, status);
            DefaultChoice(martialStatusChoice, trimString(user->getProfileRecords()[9]));
            formSizer->Add(martialStatusChoice, 0, wxALL | wxALIGN_LEFT, 5);

            AddFormField(formSizer, scrolledPanel, "Next Of Kin (NOK): ", NOKNameCtrl, user->getProfileRecords()[10]);
            AddFormField(formSizer, scrolledPanel, "NOK Contact: ", NOKContactCtrl, user->getProfileRecords()[11]);
            AddFormField(formSizer, scrolledPanel, "Medical History:", medicalHistoryCtrl, user->getProfileRecords()[12]);
            AddFormField(formSizer, scrolledPanel, "Email Address:", emailAddressCtrl, user->getProfileRecords()[13]);
            AddFormField(formSizer, scrolledPanel, "Phone Number:", phoneNumberCtrl, user->getProfileRecords()[14]);
            AddFormField(formSizer, scrolledPanel, "Address:", addressCtrl, user->getProfileRecords()[15]);
        }
        else
        {
            AddFormField(formSizer, scrolledPanel, "First Name:", firstNameCtrl, user->getProfileRecords()[2]);
            AddFormField(formSizer, scrolledPanel, "Middle Name:", middleNameCtrl, user->getProfileRecords()[3]);
            AddFormField(formSizer, scrolledPanel, "Last Name:", lastNameCtrl, user->getProfileRecords()[4]);

            wxDateTime dateStr;
            dateStr.ParseISODate(Date::toString(user->getProfileRecords()[5]));
            formSizer->Add(new wxStaticText(scrolledPanel, wxID_ANY, "DOB:"), 0, wxALL, 5);
            dobDateCtrl = new wxDatePickerCtrl(scrolledPanel, wxID_ANY,dateStr);
            formSizer->Add(dobDateCtrl, 1, wxEXPAND | wxALL, 5);

            dateStr.ParseISODate(Date::toString(user->getProfileRecords()[6]));
            formSizer->Add(new wxStaticText(scrolledPanel, wxID_ANY, "DOB:"), 0, wxALL, 5);
            doeDateCtrl = new wxDatePickerCtrl(scrolledPanel, wxID_ANY,dateStr);
            formSizer->Add(doeDateCtrl, 1, wxEXPAND | wxALL, 5);

            AddFormField(formSizer, scrolledPanel, "Assigned Department:", assignedDepartmentCtrl, user->getProfileRecords()[7]);

            formSizer->Add(new wxStaticText(scrolledPanel, wxID_ANY, "Gender:"), 0, wxALL, 5);
            wxArrayString gender;
            gender.Add("M");
            gender.Add("F");
            genderChoice = new wxChoice(scrolledPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, gender);
            DefaultChoice(genderChoice,trimString(user->getProfileRecords()[8]));
            formSizer->Add(genderChoice, 0, wxALL | wxALIGN_LEFT, 5);

            AddFormField(formSizer, scrolledPanel, "TRN:", TRN, user->getProfileRecords()[9]);
            AddFormField(formSizer, scrolledPanel, "Job Title:", jobTitleCtrl, user->getProfileRecords()[10]);

            AddFormField(formSizer, scrolledPanel, "Assigned Supervisor: ", assignedSupervisorCtrl, user->getProfileRecords()[11]);
        }
    }

    scrolledPanel->SetSizer(formSizer);
    sizer->Add(scrolledPanel, 1, wxEXPAND | wxALL, 10);

    wxBoxSizer *btnSizer = new wxBoxSizer(wxHORIZONTAL);
    wxButton *okBtn = new wxButton(this, wxID_ANY, "Confirm");
    okBtn->Bind(wxEVT_BUTTON, &EditRecordPanel::OnSubmit, this);
    btnSizer->Add(okBtn, 0, wxALL, 5);
    sizer->Add(btnSizer, 0, wxALIGN_CENTER | wxALL, 10);

    SetSizer(sizer);
    Hide();
}

EditRecordPanel::EditRecordPanel(wxDialog *parent, Appointment *apt, EditMode mode)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(300, 400))
{
    this->mode = mode;

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    this->apt = apt;
    wxDateTime wxDate;
    wxDate.ParseISODate(Date::toString(apt->getAppointmentDate()));
    vector<User *> users = UserManager::getAllUsers(2);
    wxArrayString doctors;
    for (auto &user : users)
    {
        doctors.Add("Dr." + trimString(user->getProfileRecords()[4]) + "(" + trimString(user->getProfileRecords()[1]) + ")");
    }
    doctorNumberChoice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, doctors);
    dateCtrl = new wxDatePickerCtrl(this, wxID_ANY, wxDate);

    wxArrayString times;
    times.Add("09:00 AM");
    times.Add("10:00 AM");
    times.Add("11:00 AM");
    times.Add("01:00 PM");
    times.Add("02:00 PM");
    timeChoice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, times);
    doctorNumberChoice->SetStringSelection(to_string(apt->getDoctorNumber()));
    timeChoice->SetStringSelection(apt->getAppointmentTime());

    sizer->Add(new wxStaticText(this, wxID_ANY, "Doctor:"), 0, wxALL, 5);
    sizer->Add(doctorNumberChoice, 0, wxALL | wxEXPAND, 5);
    sizer->Add(new wxStaticText(this, wxID_ANY, "Date:"), 0, wxALL, 5);
    sizer->Add(dateCtrl, 0, wxALL | wxEXPAND, 5);
    sizer->Add(new wxStaticText(this, wxID_ANY, "Time:"), 0, wxALL, 5);
    sizer->Add(timeChoice, 0, wxALL | wxEXPAND, 5);
    if (Session::GetCurrentUser()->getRole().roleLevel != "PATIENT")
    {
        statusChoice = new wxChoice(this, wxID_ANY);
        statusChoice->Append(statusToString(Status::Scheduled));
        statusChoice->Append(statusToString(Status::Completed));
        statusChoice->Append(statusToString(Status::Canceled));
        statusChoice->SetStringSelection(statusToString(apt->getStatus()));
        sizer->Add(new wxStaticText(this, wxID_ANY, "Status:"), 0, wxALL, 5);
        sizer->Add(statusChoice, 0, wxALL | wxEXPAND, 5);
    }
    wxBoxSizer *btnSizer = new wxBoxSizer(wxHORIZONTAL);
    wxButton *okBtn = new wxButton(this, wxID_ANY, "Confirm");
    okBtn->Bind(wxEVT_BUTTON, &EditRecordPanel::OnSubmit, this);
    btnSizer->Add(okBtn, 0, wxALL, 5);
    sizer->Add(btnSizer, 0, wxALIGN_CENTER | wxALL, 10);

    SetSizerAndFit(sizer);
    Hide();
}

void EditRecordPanel::OnSubmit(wxCommandEvent &event)
{
    if (this->mode == EDIT_APPOINTMENT)
    {
        if (doctorNumberChoice->GetSelection() == wxNOT_FOUND ||
            timeChoice->GetSelection() == wxNOT_FOUND)
        {
            wxMessageBox("Please fill in all fields.", "Error", wxOK | wxICON_ERROR);
            return;
        }
        apt->setDoctorNumber(getDoctorNumber());
        apt->setAppointmentDate(Date::toDate(dateCtrl->GetValue().FormatISODate().ToStdString()));
        apt->setAppointmentTime(timeChoice->GetStringSelection().ToStdString());

        if (Session::GetCurrentUser()->getRole().roleLevel != "PATIENT")
        {
            apt->setStatus(stringToStatus(statusChoice->GetStringSelection().ToStdString()));
        }
        apt->saveAppointment();
    }
    if(this->mode == EDIT_USER){
        user->setRole(Role::LoadRoleFromFile(Role::userRolePath, stoi(roleCtrl->GetValue().ToStdString())));
        user->setAttemptsRemaining(stoi(noOfAttemptsCtrl->GetValue().ToStdString()));
        if(lockedChoice->GetStringSelection().ToStdString() == "yes")
            user->toggleLock(1);
        else
            user->toggleLock(0);
        vector<string> record;
        wxDateTime dateStr;
        if(user->getRole().roleLevel == "PATIENT"){
            record.push_back(user->getProfileRecords()[0]);
            record.push_back(user->getProfileRecords()[1]);
            record.push_back(firstNameCtrl->GetValue().ToStdString());
            record.push_back(middleNameCtrl->GetValue().ToStdString());
            record.push_back(lastNameCtrl->GetValue().ToStdString());
            record.push_back(TRN->GetValue().ToStdString());
            record.push_back(dobDateCtrl->GetValue().Format("%Y-%m-%d").ToStdString());
            record.push_back(firstVisitDateCtrl->GetValue().Format("%Y-%m-%d").ToStdString());
            record.push_back(genderChoice->GetStringSelection().ToStdString());
            record.push_back(martialStatusChoice->GetStringSelection().ToStdString());
            record.push_back(NOKNameCtrl->GetValue().ToStdString());
            record.push_back(NOKContactCtrl->GetValue().ToStdString());
            record.push_back(medicalHistoryCtrl->GetValue().ToStdString());
            record.push_back(emailAddressCtrl->GetValue().ToStdString());
            record.push_back(phoneNumberCtrl->GetValue().ToStdString());
            record.push_back(addressCtrl->GetValue().ToStdString());
        }
        else
        {
            record.push_back(user->getProfileRecords()[0]);
            record.push_back(user->getProfileRecords()[1]);
            record.push_back(firstNameCtrl->GetValue().ToStdString());
            record.push_back(middleNameCtrl->GetValue().ToStdString());
            record.push_back(lastNameCtrl->GetValue().ToStdString());
            record.push_back(dobDateCtrl->GetValue().Format("%Y-%m-%d").ToStdString());
            record.push_back(doeDateCtrl->GetValue().Format("%Y-%m-%d").ToStdString());
            record.push_back(assignedDepartmentCtrl->GetValue().ToStdString());
            record.push_back(genderChoice->GetStringSelection().ToStdString());
            record.push_back(TRN->GetValue().ToStdString());
            record.push_back(jobTitleCtrl->GetValue().ToStdString());
            record.push_back(assignedSupervisorCtrl->GetValue().ToStdString());
        }
        user->setProfileRecords(record);
        UserManager::saveUserData(*user);
    }
    // Close the parent dialog manually if needed
    wxDialog* dialog = dynamic_cast<wxDialog*>(GetParent());
    if (dialog)
    {
        dialog->EndModal(wxID_OK);
    }
}


int EditRecordPanel::getDoctorNumber()
{
    string choice = this->doctorNumberChoice->GetStringSelection().ToStdString();

    size_t start = choice.find('(');
    size_t end = choice.find(')');

    if (start != string::npos && end != string::npos && end > start)
    {
        string numberStr = choice.substr(start + 1, end - start - 1);
        return stoi(numberStr);
    }
    return 0;
}
