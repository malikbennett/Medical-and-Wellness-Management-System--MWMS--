#include <Appointment.h>
#include <string>
#include <sstream>
#include <fstream>
#include <Helper.h>

string Appointment::aptInfoPath = "../../data/Appointment.csv";

Appointment::Appointment(int patientNumber, int doctorNumber, Date appointmentDate, string time, Status status)
    : patientNumber(patientNumber), doctorNumber(doctorNumber), appointmentDate(appointmentDate), appointmentTime(time), status(status)
{
    this->colSize = getFileFields(aptInfoPath).size();
    this->totalWidth = APPOINTMENT_NUMBER_LENGTH + USER_NUMBER_LENGTH + USER_NUMBER_LENGTH + DATE_LENGTH + TIME_LENGTH + STATUS_LENGTH + colSize;
    this->fieldWidths = {APPOINTMENT_NUMBER_LENGTH, USER_NUMBER_LENGTH, USER_NUMBER_LENGTH, DATE_LENGTH, TIME_LENGTH, STATUS_LENGTH};
    this->appointmentNumber = getNewAppointmentNumber();
};

Appointment::Appointment(vector<string> aptData)
    : patientNumber(stoi(aptData[1])), doctorNumber(stoi(aptData[2])), appointmentDate(aptData[3]), appointmentTime(aptData[4])
{
    this->colSize = getFileFields(aptInfoPath).size();
    this->totalWidth = APPOINTMENT_NUMBER_LENGTH + USER_NUMBER_LENGTH + USER_NUMBER_LENGTH + DATE_LENGTH + TIME_LENGTH + STATUS_LENGTH + colSize;
    this->fieldWidths = {APPOINTMENT_NUMBER_LENGTH, USER_NUMBER_LENGTH, USER_NUMBER_LENGTH, DATE_LENGTH, TIME_LENGTH, STATUS_LENGTH};
    this->appointmentNumber = getNewAppointmentNumber();
    if (aptData[5] == "Completed")
    {
        this->status = Completed;
    }
    else if (aptData[5] == "Scheduled")
    {
        this->status = Scheduled;
    }
    else
    {
        this->status = Cancelled;
    }
};

void Appointment::saveAppointment()
{
    try
    {
        fstream file(aptInfoPath, ios::in | ios::out | ios::binary);
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
            if (stoi(substr) == this->appointmentNumber)
            {
                found = true;
                break;
            }
            ++lineNum;
        }

        // Construct the new record
        string status;
        if (this->status == 0)
            status = "Completed";
        else if (this->status == 1)
            status = "Scheduled";
        else
            status = "Cancelled";

        stringstream ss;
        ss << padString(to_string(this->appointmentNumber), APPOINTMENT_NUMBER_LENGTH)
           << ',' << padString(to_string(this->patientNumber), USER_NUMBER_LENGTH)
           << ',' << padString(to_string(this->doctorNumber), USER_NUMBER_LENGTH)
           << ',' << padString(Date::toString(this->appointmentDate), DATE_LENGTH)
           << ',' << padString(this->appointmentTime, TIME_LENGTH)
           << ',' << padString(status, STATUS_LENGTH)
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
            file.seekp(start + lineNum * recordSize, ios::beg);
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

vector<Appointment *> Appointment::getAllApt()
{
    vector<Appointment *> apts;
    try
    {
        ifstream file(aptInfoPath);
        if (!file.is_open())
        {
            throw runtime_error("Appointment file failed to open");
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
            Appointment *apt = new Appointment(fields);
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


int Appointment::getNewAppointmentNumber()
{
    try
    {
        ifstream file(aptInfoPath, ios::in | ios::binary);
        if (!file.is_open())
            throw runtime_error("Appointment file failed to open");

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
        file.seekg(start + (totalRecords - 1) * recordSize, ios::beg);

        string lastLine(recordSize, '\0');
        file.read(&lastLine[0], recordSize);
        file.close();

        // Extract and return appointment number
        string aptNumStr = trimString(lastLine.substr(0, fieldWidths[0]));
        int i = stoi(aptNumStr) + 1;
        return i;
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
}

int Appointment::getAppointmentNumber() { return this->appointmentNumber; }
int Appointment::getPatientNumber() { return this->patientNumber; }
int Appointment::getDoctorNumber() { return this->doctorNumber; }
Date Appointment::getAppointmentDate() { return this->appointmentDate; }
string Appointment::getAppointmentTime() { return this->appointmentTime; }
Status Appointment::getStatus() { return this->status; }
void Appointment::setAppointmentNumber(int aptn) { this->appointmentNumber = aptn; }
void Appointment::setPatientNumber(int pn) { this->patientNumber = pn; }
void Appointment::setDoctorNumber(int dn) { this->doctorNumber = dn; }
void Appointment::setAppointmentDate(Date d) { this->appointmentDate = d; }
void Appointment::setAppointmentTime(const string &t) { this->appointmentTime = t; }
void Appointment::setStatus(Status s) { this->status = s; }
