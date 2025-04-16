#include <Patient.h>
#include <UserManager.h>
#include <iostream>

Patient::Patient(UserDataBuffer *data, PatientProfile *userProfile)
    : User(data)
{
    this->patientNumber = stoi(userProfile->records[0]);
    this->patientfirstName = userProfile->records[1];
    this->patientmiddleName = userProfile->records[2];
    this->patientlastName = userProfile->records[3];
    this->trn = stoi(userProfile->records[4]);
    this->patientDOB = Date::toDate(userProfile->records[5]);
    this->firstVisit = Date::toDate(userProfile->records[6]);
    this->patientGender = userProfile->records[7];
    this->martialStatus = userProfile->records[8];
    this->nextOfKin = userProfile->records[9];
    this->nextOfKinContact = Phone::toPhone(userProfile->records[10]);
    this->medicalHistory = userProfile->records[11];
    this->emailAddress = userProfile->records[12];
    this->phoneNumber = Phone::toPhone(userProfile->records[13]);
    this->patientAddress = Address::toAddress(userProfile->records[14]);
};

int Patient::getPatientNumber() const { return this->patientNumber; }
string Patient::getPatientFirstName() const { return this->patientfirstName; }
string Patient::getPatientMiddleName() const { return this->patientmiddleName; }
string Patient::getPatientLastName() const { return this->patientlastName; }
string Patient::getPatientGender() const { return this->patientGender; }
Date Patient::getPatientDOB() const { return this->patientDOB; }
Phone Patient::getPhoneNumber() const { return this->phoneNumber; }
Address Patient::getPatientAddress() const { return this->patientAddress; }
