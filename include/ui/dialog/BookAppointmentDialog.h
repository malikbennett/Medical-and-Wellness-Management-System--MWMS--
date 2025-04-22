#pragma once

#include <wx/wx.h>
#include <wx/datectrl.h>
#include <wx/dateevt.h>

class BookAppointmentDialog : public wxDialog {
public:
    BookAppointmentDialog(wxWindow* parent);

    int GetDoctorNumber() const;
    wxDateTime GetDate() const;
    wxString GetTimeSlot() const;

private:
    wxChoice* doctorNumberCtrl;
    wxDatePickerCtrl* dateCtrl;
    wxChoice* timeSlotCtrl;

    void OnSubmit(wxCommandEvent& event);
    void OnClose(wxCloseEvent& event);
};
