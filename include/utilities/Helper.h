#pragma once
#include <wx/wx.h>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#include <Appointment.h>

using namespace std;

inline void DefaultChoice(wxChoice *&choice,const string &value){
    int index = choice->FindString(value);
    if (index != wxNOT_FOUND)
        choice->Select(index);
}

inline void AddFormField(wxFlexGridSizer* sizer, wxWindow* parent, const wxString& label, wxTextCtrl*& ctrl, const wxString& defaultValue = "")
{
    sizer->Add(new wxStaticText(parent, wxID_ANY, label), 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
    ctrl = new wxTextCtrl(parent, wxID_ANY, defaultValue);
    sizer->Add(ctrl, 1, wxEXPAND | wxALL, 5);
}

inline wxStaticText *AddText(wxWindow *panel, wxSizer *sizer, const wxString &label, const wxFont &font, int padding = 20)
{
    wxStaticText *text = new wxStaticText(panel, wxID_ANY, label);
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
