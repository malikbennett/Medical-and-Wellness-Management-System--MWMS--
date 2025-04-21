#pragma once

#include <string>
#include <sstream>
#include <fstream>

using namespace std;

// Date structure
struct Date
{
    string day;
    string month;
    string year;
    Date(string day, string month, string year)
        : day(day), month(month), year(year) {};
    Date(string dateStr)
    {
        istringstream ssDate(dateStr);
        getline(ssDate, this->year, '-');
        getline(ssDate, this->month, '-');
        getline(ssDate, this->day, '-');
    };
    Date() {};
    static Date toDate(const string &date)
    {
        istringstream ssDate(date);
        string year, month, day;
        getline(ssDate, year, '-');
        getline(ssDate, month, '-');
        getline(ssDate, day, '-');
        return Date(day, month, year);
    }
    static string toString(const Date &date)
    {
        stringstream ssDate;
        ssDate << date.year << "-" << date.month << "-" << date.day;
        return ssDate.str();
    }
};
