#pragma once
#include <wx/wx.h>

using namespace std;

// Main app class which inherits from the wxApp class
class App : public wxApp
{
public:
    // Initial app setup, this is called to set window attributes and other main logic
    bool OnInit();
};
