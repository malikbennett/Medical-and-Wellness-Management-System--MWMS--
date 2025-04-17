#include <Patient.h>
#include <UserManager.h>
#include <iostream>
#include <string>

Patient::Patient(UserDataBuffer *data)
    : User(data)
{
    this->patientNumber = stoi(data->ProfileRecords[1]);
    this->patientfirstName = data->ProfileRecords[2];
    this->patientmiddleName = data->ProfileRecords[3];
    this->patientlastName = data->ProfileRecords[4];
    this->trn = stoi(data->ProfileRecords[5]);
    this->patientDOB = Date::toDate(data->ProfileRecords[6]);
    this->firstVisit = Date::toDate(data->ProfileRecords[7]);
    this->patientGender = data->ProfileRecords[8];
    this->martialStatus = data->ProfileRecords[9];
    this->nextOfKin = data->ProfileRecords[10];
    this->nextOfKinContact = Phone::toPhone(data->ProfileRecords[11]);
    this->medicalHistory = data->ProfileRecords[12];
    this->emailAddress = data->ProfileRecords[13];
    this->phoneNumber = Phone::toPhone(data->ProfileRecords[14]);
    this->patientAddress = Address::toAddress(data->ProfileRecords[15]);
};

int Patient::getPatientNumber() const { return this->patientNumber; }
string Patient::getPatientFirstName() const { return this->patientfirstName; }
string Patient::getPatientMiddleName() const { return this->patientmiddleName; }
string Patient::getPatientLastName() const { return this->patientlastName; }
string Patient::getPatientGender() const { return this->patientGender; }
Date Patient::getPatientDOB() const { return this->patientDOB; }
Phone Patient::getPhoneNumber() const { return this->phoneNumber; }
Address Patient::getPatientAddress() const { return this->patientAddress; }
