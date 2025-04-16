#pragma once

#include <User.h>

constexpr int PATIENT_NUMBER = 5;
constexpr int PATIENT_FIRST_NAME = 16;
constexpr int PATIENT_MIDDLE_NAME = 16;
constexpr int PATIENT_LAST_NAME = 16;
constexpr int PATIENT_GENDER = 64;
constexpr int PATIENT_DOB = 10;
constexpr int PHONE_NUMBER = 1;
constexpr int PATIENT_ADDRESS = 1;

struct PatientProfile;

// Patient Class
class Patient : public User
{
public:
    Patient(UserDataBuffer *data, PatientProfile *userProfile);
    // Getters
    int getPatientNumber() const;
    string getPatientFirstName() const;
    string getPatientMiddleName() const;
    string getPatientLastName() const;
    string getPatientGender() const;
    Date getPatientDOB() const;
    Phone getPhoneNumber() const;
    Address getPatientAddress() const;

private:
    int patientNumber, trn;
    string patientfirstName,patientmiddleName,patientlastName,patientGender;
    string medicalHistory, emailAddress, martialStatus, nextOfKin;
    Date patientDOB, firstVisit;
    Phone phoneNumber, nextOfKinContact;
    Address patientAddress;
};
