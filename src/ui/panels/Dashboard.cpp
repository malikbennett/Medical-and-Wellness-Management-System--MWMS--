#include <Dashboard.h>
#include <Helper.h>
#include <Session.h>
#include <Settings.h>
#include <Employee.h>
#include <Patient.h>
#include <ListViewCtrl.h>
#include <BookAppointmentDialog.h>
#include <Appointment.h>

Dashboard::Dashboard(wxPanel* parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize){
    this->parent = parent;
    this->headingFont = wxFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    this->paraFont = wxFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL);
}

wxPanel* Dashboard::createHomeTab()
{
    const User *user = Session::GetCurrentUser();

    wxScrolledWindow* scrolledPanel = new wxScrolledWindow(notebook);
    scrolledPanel->SetScrollRate(5, 5);
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    wxPanel *topPanel = new wxPanel(scrolledPanel, wxID_ANY,wxDefaultPosition,wxSize(200,32));
    wxBoxSizer *topSizer = new wxBoxSizer(wxHORIZONTAL);
    wxPanel *profilePanel = new wxPanel(scrolledPanel,wxID_ANY,wxDefaultPosition,wxSize(896,320));
    wxGridSizer *profileSizer = new wxGridSizer(4, 0, 0);
    wxPanel *certPanel = new wxPanel(scrolledPanel,wxID_ANY,wxDefaultPosition,wxSize(200,32));
    wxBoxSizer *certSizer = new wxBoxSizer(wxVERTICAL);

    AddText(topPanel,topSizer,"Profile:",this->headingFont,0);
    if(user->getRole().roleLevel == "PATIENT"){

        AddText(profilePanel,profileSizer,"Patient No.:",this->paraFont,0);
        AddText(profilePanel,profileSizer,trimString(user->getProfileRecords()[1]),this->paraFont,0);
        AddText(profilePanel,profileSizer,"First Name:",this->paraFont,0);
        AddText(profilePanel,profileSizer,trimString(user->getProfileRecords()[2]),this->paraFont,0);
        AddText(profilePanel,profileSizer,"Middle Name:",this->paraFont,0);
        AddText(profilePanel,profileSizer,trimString(user->getProfileRecords()[3]),this->paraFont,0);
        AddText(profilePanel,profileSizer,"Last Name:",this->paraFont,0);
        AddText(profilePanel,profileSizer,trimString(user->getProfileRecords()[4]),this->paraFont,0);
        AddText(profilePanel,profileSizer,"Email Address:",this->paraFont,0);
        AddText(profilePanel,profileSizer,trimString(user->getProfileRecords()[13]),this->paraFont,0);
        AddText(profilePanel,profileSizer,"Gender:",this->paraFont,0);
        AddText(profilePanel,profileSizer,trimString(user->getProfileRecords()[8]),this->paraFont,0);
        AddText(profilePanel,profileSizer,"Phone Number:",this->paraFont,0);
        AddText(profilePanel,profileSizer,trimString(user->getProfileRecords()[14]),this->paraFont,0);
        AddText(profilePanel,profileSizer,"Address:",this->paraFont,0);
        AddText(profilePanel,profileSizer,trimString(user->getProfileRecords()[15]),this->paraFont,0);
        AddText(profilePanel,profileSizer,"TRN:",this->paraFont,0);
        AddText(profilePanel,profileSizer,trimString(user->getProfileRecords()[5]),this->paraFont,0);
        AddText(profilePanel,profileSizer,"DOB:",this->paraFont,0);
        AddText(profilePanel,profileSizer,trimString(user->getProfileRecords()[6]),this->paraFont,0);
        AddText(profilePanel,profileSizer,"Martial Status:",this->paraFont,0);
        AddText(profilePanel,profileSizer,trimString(user->getProfileRecords()[9]),this->paraFont,0);
        AddText(profilePanel,profileSizer,"NOK:",this->paraFont,0);
        AddText(profilePanel,profileSizer,trimString(user->getProfileRecords()[10]),this->paraFont,0);
        AddText(profilePanel,profileSizer,"NOK Contact:",this->paraFont,0);
        AddText(profilePanel,profileSizer,trimString(user->getProfileRecords()[11]),this->paraFont,0);
        AddText(profilePanel,profileSizer,"Medical History:",this->paraFont,0);
        AddText(profilePanel,profileSizer,trimString(user->getProfileRecords()[12]),this->paraFont,0);
    }else{
        AddText(profilePanel,profileSizer,"Employee No.:",this->paraFont,0);
        AddText(profilePanel,profileSizer,trimString(user->getProfileRecords()[1]),this->paraFont,0);
        AddText(profilePanel,profileSizer,"Job Title:",this->paraFont,0);
        AddText(profilePanel,profileSizer,trimString(user->getProfileRecords()[10]),this->paraFont,0);
        AddText(profilePanel,profileSizer,"Assigned Department:",this->paraFont,0);
        AddText(profilePanel,profileSizer,trimString(user->getProfileRecords()[7]),this->paraFont,0);
        AddText(profilePanel,profileSizer,"Assigned Supervisor:",this->paraFont,0);
        AddText(profilePanel,profileSizer,trimString(user->getProfileRecords()[11]),this->paraFont,0);
        AddText(profilePanel,profileSizer,"First Name:",this->paraFont,0);
        AddText(profilePanel,profileSizer,trimString(user->getProfileRecords()[2]),this->paraFont,0);
        AddText(profilePanel,profileSizer,"Middle Name:",this->paraFont,0);
        AddText(profilePanel,profileSizer,trimString(user->getProfileRecords()[3]),this->paraFont,0);
        AddText(profilePanel,profileSizer,"Last Name:",this->paraFont,0);
        AddText(profilePanel,profileSizer,trimString(user->getProfileRecords()[4]),this->paraFont,0);
        AddText(profilePanel,profileSizer,"Gender:",this->paraFont,0);
        AddText(profilePanel,profileSizer,trimString(user->getProfileRecords()[8]),this->paraFont,0);
        AddText(profilePanel,profileSizer,"TRN:",this->paraFont,0);
        AddText(profilePanel,profileSizer,trimString(user->getProfileRecords()[9]),this->paraFont,0);
        AddText(profilePanel,profileSizer,"DOB:",this->paraFont,0);
        AddText(profilePanel,profileSizer,trimString(user->getProfileRecords()[5]),this->paraFont,0);
        AddText(profilePanel,profileSizer,"Date of Employment:",this->paraFont,0);
        AddText(profilePanel,profileSizer,trimString(user->getProfileRecords()[6]),this->paraFont,0);
    }

    if(user->getRole().roleLevel != "PATIENT"){
        AddText(certPanel,certSizer,"Certification:",this->headingFont,0);
        AddText(certPanel,certSizer,"No cerification unfortunately....",this->paraFont,0);
    }

    sizer->Add(topPanel, 0, wxEXPAND | wxALL, 16);
    sizer->Add(profilePanel, 0, wxEXPAND | wxALL, 16);
    sizer->Add(certPanel, 1, wxEXPAND | wxALL, 16);

    topPanel->SetSizer(topSizer);
    profilePanel->SetSizer(profileSizer);
    certPanel->SetSizer(certSizer);
    scrolledPanel->SetSizer(sizer);
    return scrolledPanel;
}

wxPanel *Dashboard::createAppointmentsTab()
{
    wxPanel *panel = new wxPanel(notebook);
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);


    wxPanel *topPanel = new wxPanel(panel);
    wxBoxSizer *topSizer = new wxBoxSizer(wxHORIZONTAL);
    AddText(topPanel, topSizer, "Appointments:", this->headingFont);
    wxButton *bookAptBtn = new wxButton(topPanel,wxID_OK, "Book Appointment");
    bookAptBtn->SetBackgroundColour(Settings::getInstance().colors.primary);
    bookAptBtn->Bind(wxEVT_BUTTON, &Dashboard::OnBookAppointment, this);
    topSizer->AddStretchSpacer();
    topSizer->Add(bookAptBtn, 0, wxALIGN_CENTER | wxALL, 15);
    topPanel->SetSizer(topSizer);

    wxPanel *bottomPanel = new wxPanel(panel);
    wxBoxSizer *bottomSizer = new wxBoxSizer(wxVERTICAL);
    ListView *list = new ListView(bottomPanel,wxID_ANY,wxDefaultPosition,wxDefaultSize);
    list->loadAppointmentsFields();
    list->RefreshAfterUpdate();
    bottomSizer->Add(list, 1, wxEXPAND);
    bottomPanel->SetSizer(bottomSizer);

    sizer->Add(topPanel,0,wxEXPAND);
    sizer->Add(bottomPanel,1,wxEXPAND);

    panel->SetSizer(sizer);
    return panel;
};

void Dashboard::OnBookAppointment(wxCommandEvent& event)
{
    BookAppointmentDialog dlg(this);
    if (dlg.ShowModal() == wxID_OK)
    {
        const User *user = Session::GetCurrentUser();
        const Employee *emp = dynamic_cast<const Employee *>(user);
        const Patient *pat = dynamic_cast<const Patient *>(user);
        int doctorNumber = dlg.GetDoctorNumber();
        Date date(dlg.GetDate().Format("%Y-%m-%d").ToStdString());
        string time = dlg.GetTimeSlot().ToStdString();
        if (pat)
        {
            Appointment apt(pat->getPatientNumber(),doctorNumber,date,time ,Status::Scheduled);
            apt.saveAppointment();
        }
        else if (emp)
        {
            Appointment apt(emp->getId(),doctorNumber,date,time ,Status::Scheduled);
            apt.saveAppointment();
        }
        wxLogMessage("Booking: Doctor #%d on %s at %s",doctorNumber,dlg.GetDate().FormatISODate(),time);
    }
}
