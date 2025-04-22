#pragma once

#include <wx/wx.h>
#include <User.h>
#include <Appointment.h>
#include <Prescription.h>
#include <UserManager.h>
#include <wx/datectrl.h>
#include <wx/dateevt.h>

enum EditMode {
    EDIT_PRESCRIPTION,
    EDIT_APPOINTMENT,
    EDIT_USER
};

class EditRecordPanel : public wxPanel
{
public:
    EditRecordPanel(wxDialog *parent, User *user, EditMode mode);
    EditRecordPanel(wxDialog *parent, Appointment *apt, EditMode mode);
    EditRecordPanel(wxDialog *parent, Prescription *pres, EditMode mode);

    static int GetNumber(wxChoice* Ctrl);
    wxChoice *GetMedProfChoice() const;

private:
    EditMode mode;

    User* user;
    wxTextCtrl *userNameCtrl;
    wxTextCtrl *passwordCtrl;
    wxTextCtrl *roleCtrl;
    wxTextCtrl *noOfAttemptsCtrl;
    wxChoice* lockedChoice;

    wxTextCtrl *firstNameCtrl;
    wxTextCtrl *middleNameCtrl;
    wxTextCtrl *lastNameCtrl;
    wxTextCtrl *TRN;
    wxDatePickerCtrl* dobDateCtrl;
    wxDatePickerCtrl* doeDateCtrl;
    wxDatePickerCtrl* firstVisitDateCtrl;
    wxChoice* genderChoice;
    wxChoice* martialStatusChoice;
    wxTextCtrl *NOKNameCtrl;
    wxTextCtrl *NOKContactCtrl;
    wxTextCtrl *medicalHistoryCtrl;
    wxTextCtrl *emailAddressCtrl;
    wxTextCtrl *assignedDepartmentCtrl;
    wxTextCtrl *assignedSupervisorCtrl;
    wxTextCtrl *phoneNumberCtrl;
    wxTextCtrl *addressCtrl;
    wxTextCtrl *jobTitleCtrl;

    Appointment *apt;
    wxDatePickerCtrl* dateCtrl;
    wxChoice* timeChoice;
    wxChoice* statusChoice;
    wxChoice *medProfNumberChoice;

    Prescription *pres;
    wxTextCtrl *medicationCtrl;
    wxTextCtrl *dosageCtrl;

    void OnSubmit(wxCommandEvent &event);
};
