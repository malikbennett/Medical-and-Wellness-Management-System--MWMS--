#pragma once

#include <User.h>

// Defines Different Status States
enum Status
{
    Completed,
    Scheduled,
    Cancelled
};

class Appointment{
private:
    int appointmentNumber;
    int patientNumber;
    int doctorNumber;
    Date appointmentDate;
    Status status;
};
