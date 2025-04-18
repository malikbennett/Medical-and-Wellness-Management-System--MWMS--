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
    this->paraFont = wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL);
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

wxPanel *Dashboard::createAppointmentsTab()
{
    wxPanel *panel = new wxPanel(notebook);
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    AddText(panel, sizer, "Appointments:", this->headingFont);

    wxPanel *topPanel = new wxPanel(panel);
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    wxButton *bookAptBtn = new wxButton(topPanel,wxID_OK, "Book Appointment");
    bookAptBtn->SetBackgroundColour(Settings::getInstance().colors.primary);
    bookAptBtn->Bind(wxEVT_BUTTON, &Dashboard::OnBookAppointment, this);
    topSizer->Add(bookAptBtn, 0, wxALIGN_RIGHT | wxALL, 5);
    topPanel->SetSizer(topSizer);

    wxPanel *bottomPanel = new wxPanel(panel);
    wxBoxSizer *bottomSizer = new wxBoxSizer(wxVERTICAL);
    ListView *list = new ListView(bottomPanel,wxID_ANY,wxDefaultPosition,wxDefaultSize);
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
        int doctorNumber = dlg.GetDoctorNumber();
        Date date(dlg.GetDate().Format("%Y-%m-%d").ToStdString());
        string time = dlg.GetTimeSlot().ToStdString();

        Appointment apt(Session::GetCurrentUser()->getUserNumber(),doctorNumber,date,time ,Scheduled);
        apt.saveAppointment();

        // TODO: Save to file here
        wxLogMessage("Booking: Doctor #%d on %s at %s",doctorNumber,dlg.GetDate().FormatISODate(),time);
    }
}
