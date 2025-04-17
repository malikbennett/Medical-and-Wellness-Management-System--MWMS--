#pragma once

#include <User.h>
#include <string>
#include <Helper.h>

struct PatientProfile;

// Patient Class
class Patient : public User
{
public:
    Patient(UserDataBuffer *data);
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
