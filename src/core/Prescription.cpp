#include <Prescription.h>
#include <Helper.h>
#include <sstream>
#include <fstream>
#include <string>

string Prescription::presInfoPath = "../../data/Prescription.csv";

Prescription::Prescription(int prescriptionNumber,int patientNumber,int doctorNumber, Date prescriptionDate, string medication, double dosage)
    : patientNumber(patientNumber), doctorNumber(doctorNumber), prescriptionDate(prescriptionDate), medication(medication), dosage(dosage)
{
    this->colSize = getFileFields(presInfoPath).size();
    this->totalWidth = colSize;
    this->fieldWidths = {ID_NUMBER_LENGTH, ID_NUMBER_LENGTH, ID_NUMBER_LENGTH, DATE_LENGTH, MEDICATION_LENGTH,DOSAGE_LENGTH};
    for(auto &field : fieldWidths){
        totalWidth += field;
    }
    this->prescriptionNumber = getNewPrescriptionNumber();
};

Prescription::Prescription(vector<string> presData)
    : prescriptionNumber(stoi(presData[0])), patientNumber(stoi(presData[1])), doctorNumber(stoi(presData[2])), prescriptionDate(presData[3]),
    medication(presData[4]), dosage(stod(presData[5]))
{
    this->colSize = getFileFields(presInfoPath).size();
    this->totalWidth = colSize;
    this->fieldWidths = {ID_NUMBER_LENGTH, ID_NUMBER_LENGTH, ID_NUMBER_LENGTH, DATE_LENGTH, MEDICATION_LENGTH,DOSAGE_LENGTH};
    for(auto &field : fieldWidths){
        totalWidth += field;
    }
};

void Prescription::savePrescription()
{
    try
    {
        fstream file(presInfoPath, ios::in | ios::out | ios::binary);
        if (!file.is_open())
            throw runtime_error("User File Information Could not open");

        string header;
        getline(file, header); // Skip header

        streampos start = file.tellg(); // Mark start of records

        string line;
        int lineNum = 0;
        bool found = false;

        while (getline(file, line))
        {
            string substr = trimString(line.substr(0, fieldWidths[0]));
            if (stoi(substr) == this->prescriptionNumber)
            {
                found = true;
                break;
            }
            ++lineNum;
        }

        // Construct the new record
        stringstream ss;
        ss << padString(to_string(this->prescriptionNumber), ID_NUMBER_LENGTH)
           << ',' << padString(to_string(this->patientNumber), ID_NUMBER_LENGTH)
           << ',' << padString(to_string(this->doctorNumber), ID_NUMBER_LENGTH)
           << ',' << padString(Date::toString(this->prescriptionDate), DATE_LENGTH)
           << ',' << padString(this->medication, MEDICATION_LENGTH)
           << ',' << padString(to_string(this->dosage), DOSAGE_LENGTH)
           << ',';

        string record = ss.str();

        if (record.length() != totalWidth)
        {
            cerr << "Record length mismatch. Record is " << record.length()
                 << ", expected " << totalWidth << endl;
            file.close();
            return;
        }

        if (found)
        {
            // Go to correct offset (start + lineNum * recordSize)
            int recordSize = totalWidth + 1; // +1 for newline
            file.seekp(start + static_cast<streamoff>(lineNum * recordSize), ios::beg);
            file << record << '\n'; // overwrite
        }
        else
        {
            // Append new line at end
            file.clear(); // Clear EOF flag
            file.seekp(0, ios::end);
            file << record << '\n';
        }

        file.close();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

vector<Prescription *> Prescription::getAllPres()
{
    vector<Prescription *> apts;
    try
    {
        ifstream file(presInfoPath);
        if (!file.is_open())
        {
            throw runtime_error("Prescription file failed to open");
        }
        string header;
        getline(file, header);
        string line;
        while (getline(file, line))
        {
            istringstream ss(line);
            string token;
            vector<string> fields;
            while (getline(ss, token, ','))
            {
                fields.push_back(token);
            }
            if (fields.size() != 6)
            {
                std::cerr << "Skipping invalid row: " << line << std::endl;
                continue;
            }
            Prescription *apt = new Prescription(fields);
            apts.push_back(apt);
        }
        std::cout << "Total appointments loaded: " << apts.size() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error in getAllApt(): " << e.what() << '\n';
    }
    return apts;
}

int Prescription::getNewPrescriptionNumber()
{
    try
    {
        ifstream file(presInfoPath, ios::in | ios::binary);
        if (!file.is_open())
            throw runtime_error("Prescription file failed to open");

        string header;
        getline(file, header); // Skip variable-length header line

        streampos start = file.tellg(); // Marks start of fixed-length records

        file.seekg(0, ios::end);
        streampos end = file.tellg();

        int recordSize = totalWidth + 1; // +1 for newline

        streamoff dataSize = end - start;

        if (dataSize < recordSize)
            return 1; // No actual data records

        int totalRecords = dataSize / recordSize;

        // Go to the last record
        file.seekg(start + static_cast<streamoff>((totalRecords - 1) * recordSize), ios::beg);

        string lastLine(recordSize, '\0');
        file.read(&lastLine[0], recordSize);
        file.close();

        // Extract and return appointment number
        string presNumStr = trimString(lastLine.substr(0, fieldWidths[0]));
        int i = stoi(presNumStr) + 1;
        return i;
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
}

int Prescription::getPrescriptionNumber() { return this->prescriptionNumber; }
int Prescription::getPatientNumber() { return this->patientNumber; }
int Prescription::getDoctorNumber() { return this->doctorNumber; }
Date Prescription::getPrescriptionDate() { return this->prescriptionDate; }
string Prescription::getMedication() { return this->medication; }
double Prescription::getDosage() { return this->dosage; }
void Prescription::setPrescriptionNumber(int aptn) { this->prescriptionNumber = aptn; }
void Prescription::setPatientNumber(int pn) { this->patientNumber = pn; }
void Prescription::setDoctorNumber(int dn) { this->doctorNumber = dn; }
void Prescription::setPrescriptionDate(Date d) { this->prescriptionDate = d; }
void Prescription::setDosage(double d) { this->dosage = d; }
void Prescription::setMedication(const string &m) { this->medication = m; }
