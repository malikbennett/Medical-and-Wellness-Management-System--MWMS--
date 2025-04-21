#include <Patient.h>
#include <iostream>
#include <string>

Patient::Patient(User &data)
    : User(data)
{
    auto pR = data.getProfileRecords();
    this->patientNumber = stoi(pR[1]);
    this->patientfirstName =trimString(pR[2]);
    this->patientmiddleName =trimString(pR[3]);
    this->patientlastName =trimString(pR[4]);
    this->trn = stoi(pR[5]);
    this->patientDOB = Date::toDate(pR[6]);
    this->firstVisit = Date::toDate(pR[7]);
    this->patientGender =trimString(pR[8]);
    this->martialStatus =trimString(pR[9]);
    this->nextOfKin =trimString(pR[10]);
    this->nextOfKinContact = Phone::toPhone(pR[11]);
    this->medicalHistory =trimString(pR[12]);
    this->emailAddress =trimString(pR[13]);
    this->phoneNumber = Phone::toPhone(pR[14]);
    this->patientAddress = Address::toAddress(pR[15]);
};

int Patient::getPatientNumber() const { return this->patientNumber; }
string Patient::getPatientFirstName() const { return this->patientfirstName; }
string Patient::getPatientMiddleName() const { return this->patientmiddleName; }
string Patient::getPatientLastName() const { return this->patientlastName; }
string Patient::getPatientGender() const { return this->patientGender; }
Date Patient::getPatientDOB() const { return this->patientDOB; }
Phone Patient::getPhoneNumber() const { return this->phoneNumber; }
Address Patient::getPatientAddress() const { return this->patientAddress; }
