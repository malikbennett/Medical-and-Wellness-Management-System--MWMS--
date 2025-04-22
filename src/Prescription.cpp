#include "core/Prescription.h"
#include <fstream>        
#include <iostream>    


void Prescription::approve() {
    isApproved = true;
}



bool Prescription::getApprovalStatus() const {
    return isApproved;
}


void Prescription::saveToFile(std::ofstream& out) const {
    out << prescriptionNumber << ','
        << patientNumber << ','
        << doctorNumber << ','
        << medication << ','
        << dosage << ','
        << prescriptionDate.day << '/'
        << prescriptionDate.month << '/'
        << prescriptionDate.year << ','
        << isApproved << '\n';
}


void Prescription::loadFromFile(std::ifstream& in) {
    char comma, slash;
    std::string med;
    std::getline(in, med, ','); 

    in >> prescriptionNumber >> comma
       >> patientNumber >> comma
       >> doctorNumber >> comma;

    std::getline(in, medication, ',');
    in >> dosage >> comma
       >> prescriptionDate.day >> slash
       >> prescriptionDate.month >> slash
       >> prescriptionDate.year >> comma
       >> isApproved;
}

bool Prescription::getApprovalStatus() const {
    return isApproved;
}

