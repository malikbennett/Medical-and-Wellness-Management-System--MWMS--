#pragma once

#include <User.h>
#include <Helper.h>
#include <Constants.h>

using namespace std;

// Defines Different Status States
enum Status
{
    Completed,
    Scheduled,
    Cancelled
};

class Appointment
{
public:
    Appointment(int patientNumber,int doctorNumber,Date appointmentDate,string time,Status status);
    void saveAppointment();
    // Getters and Setters
    int getNewAppointmentNumber();
    int getAppointmentNumber();
    int getPatientNumber();
    int getDoctorNumber();
    Date getAppointmentDate();
    string getAppointmentTime();
    Status getStatus();
    void setAppointmentNumber(int aptn);
    void setPatientNumber(int pn);
    void setDoctorNumber(int dn);
    void setAppointmentDate(Date d);
    void setAppointmentTime(const string& t);
    void setStatus(Status s);

private:
    int appointmentNumber;
    int patientNumber;
    int doctorNumber;
    Date appointmentDate;
    string appointmentTime;
    Status status;
    string aptInfoPath = "../../data/Appointment.csv";
    int colSize;
    vector<int> fieldWidths;
    int totalWidth;
};
