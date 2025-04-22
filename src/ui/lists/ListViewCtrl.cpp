#include <ListViewCtrl.h>
#include <EditRecordPanel.h>
#include <ActionDialog.h>

ListView::ListView(wxPanel *parent, wxWindowID id, const wxPoint &pos, const wxSize &size)
    : wxListCtrl(parent, id, pos, size, wxLC_REPORT | wxLC_VIRTUAL)
{
    Bind(wxEVT_LIST_ITEM_ACTIVATED, &ListView::OnItemActivated, this);
    this->usrfields = getFileFields(UserManager::userInfoPath);
    this->empfields = getFileFields(UserManager::employeeInfoPath);
    this->patfields = getFileFields(UserManager::patientInfoPath);
    this->aptfields = getFileFields(Appointment::aptInfoPath);
    this->presfields = getFileFields(Prescription::presInfoPath);
    this->parent = parent;
};

void ListView::loadEmployeeFields()
{
    auto allUsers = UserManager::getAllUsers();
    this->users.clear();
    // Only keep users who are NOT patients
    for (auto *user : allUsers)
    {
        if (user->getRole().roleLevel != "PATIENT")
        {
            this->users.push_back(user);
        }
    }

    if (users.empty())
    {
        wxMessageBox("No users found.");
        return;
    }
    // Clear previous columns
    this->ClearAll();
    int colIndex = 0;
    for (size_t i = 0; i < usrfields.size() && i < 6; ++i)
    {
        this->InsertColumn(colIndex++, usrfields[i], wxLIST_FORMAT_LEFT, 120);
    }
    for (size_t i = 1; i < empfields.size() && i <= 11; ++i)
    {
        this->InsertColumn(colIndex++, empfields[i], wxLIST_FORMAT_LEFT, 120);
    }
}

void ListView::loadPatientFields()
{
    auto allUsers = UserManager::getAllUsers();
    this->users.clear();
    // Only keep users who are patients (i.e., roleId = 7)
    for (auto *user : allUsers)
    {
        if (user->getRole().roleLevel == "PATIENT")
        {
            this->users.push_back(user);
        }
    }
    if (users.empty())
    {
        wxMessageBox("No users found.");
        return;
    }
    // Clear previous columns
    this->ClearAll();
    int colIndex = 0;
    for (size_t i = 0; i < usrfields.size() && i < 6; ++i)
    {
        this->InsertColumn(colIndex++, usrfields[i], wxLIST_FORMAT_LEFT, 120);
    }
    for (size_t i = 1; i < patfields.size() && i <= 15; ++i)
    {
        this->InsertColumn(colIndex++, patfields[i], wxLIST_FORMAT_LEFT, 120);
    }
}

void ListView::loadAppointmentsFields()
{
    auto allApts = Appointment::getAllApt();
    const User *user = Session::GetCurrentUser();
    const Patient *pat = dynamic_cast<const Patient *>(user);
    const Employee *emp = dynamic_cast<const Employee *>(user);
    this->apts.clear();
    if (user->getRole().roleLevel == "PATIENT" && pat)
    {
        for (auto *apt : allApts)
        {
            if (apt->getPatientNumber() == pat->getPatientNumber())
                this->apts.push_back(apt);
        }
    }
    if (user->getRole().roleLevel == "MEDICAL_PROFESSIONAL" && emp)
    {
        for (auto *apt : allApts)
        {
            if (apt->getDoctorNumber() == emp->getId())
                this->apts.push_back(apt);
        }
    }
    if (user->getRole().roleLevel == "ADMIN" || user->getRole().roleLevel == "SUPPORT_STAFF")
    {
        this->apts = allApts;
    }
    if (this->apts.empty())
    {
        wxMessageBox("No Appointments found.");
        return;
    }
    this->ClearAll();
    int colIndex = 0;
    for (size_t i = 0; i < this->aptfields.size() && i <= 5; ++i)
    {
        this->InsertColumn(colIndex++, this->aptfields[i], wxLIST_FORMAT_LEFT, 120);
    }
}

void ListView::loadPrescriptionFields()
{
    auto allPres = Prescription::getAllPres();
    const User *user = Session::GetCurrentUser();
    const Patient *pat = dynamic_cast<const Patient *>(user);
    this->pres.clear();
    if (user->getRole().roleLevel == "MEDICAL_PROFESSIONAL" || user->getRole().roleLevel == "ADMIN" || user->getRole().roleLevel == "SUPPORT_STAFF")
    {
        this->pres = allPres;
    }
    if (this->pres.empty())
    {
        wxMessageBox("No Prescriptions found.");
        return;
    }
    this->ClearAll();
    int colIndex = 0;
    for (size_t i = 0; i < this->presfields.size() && i <= 5; ++i)
    {
        this->InsertColumn(colIndex++, this->presfields[i], wxLIST_FORMAT_LEFT, 120);
    }
}

wxString ListView::OnGetItemText(long index, long column) const
{
    if (!this->apts.empty())
    {
        Appointment *apt = this->apts.at(index);
        switch (column)
        {
        case 0:
            return to_string(apt->getAppointmentNumber());
        case 1:
            return to_string(apt->getPatientNumber());
        case 2:
            return to_string(apt->getDoctorNumber());
        case 3:
            return Date::toString(apt->getAppointmentDate());
        case 4:
            return apt->getAppointmentTime();
        case 5:
            return statusToString(apt->getStatus());
        }
    }
    else if (!this->users.empty())
    {
        User *user = this->users.at(index);
        switch (column)
        {
        case 0:
            return wxString::Format("%d", user->getUserNumber());
        case 1:
            return trimString(user->getUsername());
        case 2:
            return trimString(user->getPassword());
        case 3:
            return wxString::Format("%d", user->getRole().roleNumber);
        case 4:
            return wxString::Format("%d", user->getAttemptsRemaining());
        case 5:
            return (user->locked()) ? "yes" : "no";
        }
        // Only access Employee Profile fields
        if (user->getRole().roleLevel != "PATIENT")
        {
            switch (column)
            {
            case 6:
                return user->getProfileRecords()[1];
            case 7:
                return user->getProfileRecords()[2];
            case 8:
                return user->getProfileRecords()[3];
            case 9:
                return user->getProfileRecords()[4];
            case 10:
                return user->getProfileRecords()[5];
            case 11:
                return user->getProfileRecords()[6];
            case 12:
                return user->getProfileRecords()[7];
            case 13:
                return user->getProfileRecords()[8];
            case 14:
                return user->getProfileRecords()[9];
            case 15:
                return user->getProfileRecords()[10];
            case 16:
                return user->getProfileRecords()[11];
            }
        }
        // Only access Patient Profile fields
        if (user->getRole().roleLevel == "PATIENT")
        {
            switch (column)
            {
            case 6:
                return user->getProfileRecords()[1];
            case 7:
                return user->getProfileRecords()[2];
            case 8:
                return user->getProfileRecords()[3];
            case 9:
                return user->getProfileRecords()[4];
            case 10:
                return user->getProfileRecords()[5];
            case 11:
                return user->getProfileRecords()[6];
            case 12:
                return user->getProfileRecords()[7];
            case 13:
                return user->getProfileRecords()[8];
            case 14:
                return user->getProfileRecords()[9];
            case 15:
                return user->getProfileRecords()[10];
            case 16:
                return user->getProfileRecords()[11];
            case 17:
                return user->getProfileRecords()[12];
            case 18:
                return user->getProfileRecords()[13];
            case 19:
                return user->getProfileRecords()[14];
            case 20:
                return user->getProfileRecords()[15];
            }
        }
    }
    else if (!this->pres.empty())
    {
        Prescription *pres = this->pres.at(index);
        switch (column)
        {
        case 0:
            return to_string(pres->getPrescriptionNumber());
        case 1:
            return to_string(pres->getPatientNumber());
        case 2:
            return to_string(pres->getDoctorNumber());
        case 3:
            return Date::toString(pres->getPrescriptionDate());
        case 4:
            return pres->getMedication();
        case 5:
            return to_string(pres->getDosage());
        }
    }

    return " ";
}

void ListView::RefreshAfterUpdate()
{
    if (!this->apts.empty())
    {
        this->SetItemCount(this->apts.size());
    }
    else if (!this->users.empty())
    {
        this->SetItemCount(this->users.size());
    }
    else if (!this->pres.empty())
    {
        this->SetItemCount(this->pres.size());
    }
    this->Refresh();
}

void ListView::OnItemActivated(wxListEvent &event)
{
    ActionDialog *dialog;
    this->index = event.GetIndex();
    Appointment *selectedApt = nullptr;
    Prescription *selectedPres = nullptr;
    User *selectedUser = nullptr;

    if (index >= 0 && index < (int)apts.size())
    {
        selectedApt = apts[index];
    }

    if (index >= 0 && index < (int)users.size())
    {
        selectedUser = users[index];
    }

    if (index >= 0 && index < (int)pres.size())
    {
        selectedPres = pres[index];
    }
    dialog = new ActionDialog(this->parent, selectedApt, selectedUser, selectedPres);
    dialog->ShowModal();
    dialog->Destroy(); // Clean up to prevent memory leak

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
};
