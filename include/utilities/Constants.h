#pragma once

#include <wx/colour.h>

struct ColorPalette {
    wxColor background;
    wxColor surface;
    wxColor surfaceLight;

    wxColor primary;
    wxColor primaryDark;

    wxColor secondary;
    wxColor secondaryDark;

    wxColor textPrimaryLight;
    wxColor textPrimary;
    wxColor textPrimaryDark;

    wxColor textSecondaryLight;
    wxColor textSecondary;
    wxColor textSecondaryDark;

    wxColor error;
};

constexpr int BASIC_LENGTH_10 = 10;
constexpr int BASIC_LENGTH_12 = 12;
constexpr int BASIC_LENGTH_16 = 16;
constexpr int BASIC_LENGTH_32 = 32;
constexpr int BASIC_LENGTH_64 = 64;

constexpr int USER_NUMBER_LENGTH = 5;
constexpr int USERNAME_LENGTH = BASIC_LENGTH_16;
constexpr int PASSWORD_LENGTH = BASIC_LENGTH_64;
constexpr int ROLE_NUMBER_LENGTH = 2;
constexpr int ATTEMPTS_REMAINING_LENGTH = 1;
constexpr int ACCOUNT_LOCKED_LENGTH = 1;

constexpr int NAME_LENGTH = BASIC_LENGTH_16;
constexpr int GENDER_LENGTH = 1;
constexpr int TRN_LENGTH = BASIC_LENGTH_10;
constexpr int MARTIAL_STATUS_LENGTH = BASIC_LENGTH_10;
constexpr int NOK_LENGTH = BASIC_LENGTH_32;
constexpr int MEDICAL_HISTORY_LENGTH = BASIC_LENGTH_32;
constexpr int PHONE_NUMBER_LENGTH = BASIC_LENGTH_12;
constexpr int DATE_LENGTH = BASIC_LENGTH_10;
constexpr int EMAIL_ADDRESS_LENGTH = BASIC_LENGTH_32;
constexpr int ADDRESS_LENGTH = BASIC_LENGTH_64;


constexpr int DEPARTMENT_LENGTH = BASIC_LENGTH_16;
constexpr int JOB_TITLE_LENGTH = BASIC_LENGTH_16;

constexpr int APPOINTMENT_NUMBER_LENGTH = 5;   // e.g. 00001
constexpr int TIME_LENGTH = 8;   // e.g. 00012
constexpr int STATUS_LENGTH = BASIC_LENGTH_10;  // e.g. "Scheduled", "Completed", "Cancelled"
