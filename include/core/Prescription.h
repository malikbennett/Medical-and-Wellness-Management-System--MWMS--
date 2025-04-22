#pragma once

#include <User.h>
#include <Helper.h>

using namespace std;

class Prescription {
public:
public:
    Prescription(int prescriptionNumber,int patientNumber,int doctorNumber, Date prescriptionDate, string medication, double dosage);
    Prescription(vector<string> presData);
    void savePrescription();

    // Getters and Setters
    static vector<Prescription *> getAllPres();
    int getNewPrescriptionNumber();
    int getPrescriptionNumber();
    int getPatientNumber();
    int getDoctorNumber();
    Date getPrescriptionDate();
    string getMedication();
    double getDosage();
    void setPrescriptionNumber(int aptn);
    void setPatientNumber(int pn);
    void setDoctorNumber(int dn);
    void setPrescriptionDate(Date d);
    void setMedication(const string& m);
    void setDosage(double d);
    static string presInfoPath;
private:
    int prescriptionNumber;
    int patientNumber;
    int doctorNumber;
    string medication;
    double dosage;
    Date prescriptionDate;
    int colSize;
    vector<int> fieldWidths;
    int totalWidth;
};
