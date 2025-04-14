#pragma once

#include <User.h>

using namespace std;

class Prescription {
private:
    int precrtiptionNumber;
    int patientNumber;
    int doctorNumber;
    string medication;
    double dosage;
    Date prescriptionDate;
};
