#pragma once

#include <wx/wx.h>
#include <wx/datectrl.h>
#include <wx/dateevt.h>

class BookAppointmentDialog : public wxDialog {
public:
    BookAppointmentDialog(wxWindow* parent);

    static int GetNumber(wxChoice* Ctrl);
    wxDateTime GetDate() const;
    wxString GetTimeSlot() const;
    wxChoice *GetPatientCtrl() const;
    wxChoice *GetMedProfCtrl() const;

private:
    wxChoice* patientNumberCtrl;
    wxChoice* medProfNumberCtrl;
    wxDatePickerCtrl* dateCtrl;
    wxChoice* timeSlotCtrl;

    void OnSubmit(wxCommandEvent& event);
    void OnClose(wxCloseEvent& event);
};
