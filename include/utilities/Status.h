#pragma once

#include <string>
#include <sstream>
#include <fstream>

using namespace std;

// Defines Different Status States
enum class Status
{
    Completed,
    Scheduled,
    Canceled
};


inline Status stringToStatus(string statusStr)
{
    Status status;
    if (statusStr == "Completed")
    {
        status = Status::Completed;
    }
    else if (statusStr == "Scheduled")
    {
        status = Status::Scheduled;
    }
    else
    {
        status = Status::Canceled;
    }
    return status;
};

inline string statusToString(Status status)
{
    string statusStr;
    if (status == Status::Completed)
    {
        statusStr = "Completed";
    }
    else if (status == Status::Scheduled)
    {
        statusStr = "Scheduled";
    }
    else
    {
        statusStr = "Canceled";
    }
    return statusStr;
};
