#pragma once
#include <wx/wx.h>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

// PhoneNumber class
class Phone
{
public:
    Phone(int areaCode, int exchange, int lineNumber)
        : areaCode(areaCode), exchange(exchange), lineNumber(lineNumber) {};
    Phone() {};
    static Phone toPhone(const string &phone)
    {
        string areaCode, exchange, lineNumber;
        istringstream phoneStream(phone);
        getline(phoneStream, areaCode, '-');
        getline(phoneStream, exchange, '-');
        getline(phoneStream, lineNumber, '-');
        return Phone(stoi(areaCode), stoi(exchange), stoi(lineNumber));
    }

private:
    int areaCode;
    int exchange;
    int lineNumber;
};
// Address Class
class Address
{
public:
    Address(int streetNumber, string streetName, string parish, string country)
        : streetNumber(streetNumber), streetName(streetName),
        parish(parish), country(country) {};
    Address() {};
    static Address toAddress(const string &address)
    {
        string streetNumber, streetName, parish, country;
        istringstream addressStream(address);
        getline(addressStream, streetNumber, '-');
        getline(addressStream, streetName, '-');
        getline(addressStream, parish, '-');
        getline(addressStream, country, '-');
        return Address(stoi(streetNumber), streetName, parish, country);
    }

private:
    int streetNumber;
    string streetName;
    string parish;
    string country;
};
// Date structure
struct Date
{
    string day;
    string month;
    string year;
    Date(string day, string month, string year)
        : day(day), month(month), year(year) {};
    Date(string dateStr){
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


inline wxStaticText* AddText(wxPanel* panel, wxSizer* sizer, const wxString& label, const wxFont& font, int padding = 20) {
    wxStaticText* text = new wxStaticText(panel, wxID_ANY, label);
    text->SetFont(font);
    sizer->Add(text, 0, wxALIGN_LEFT | wxALL, padding);
    return text;
}

inline string padString(const string &value, int width)
{
    string padded = value;
    padded.resize(width, ' ');
    return padded;
}
inline string trimString(const string &str)
{
    size_t first = str.find_first_not_of(' ');
    if (first == string::npos)
        return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

inline vector<string> getFileFields(const string &filePath)
{
    vector<string> fields;
    try
    {
        ifstream file;
        file.open(filePath);
        if (file.fail())
        {
            throw runtime_error("File fail to open");
        }
        string line;
        getline(file, line);
        istringstream ss(line);
        string token;
        while (getline(ss, token, ','))
        {
            fields.push_back(token);
        }
        if (fields.empty())
        {
            throw runtime_error("Error retrieving fields");
        }
        return fields;
    }
    catch (exception e)
    {
        cerr << e.what() << endl;
    }
    return fields;
};
