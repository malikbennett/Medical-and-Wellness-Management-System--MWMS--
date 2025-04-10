#include <HomePanel.h>
#include <Settings.h>
#include <iostream>

HomePanel::HomePanel(wxPanel* parentPanel) : wxPanel(parentPanel, wxID_ANY, wxDefaultPosition, wxSize(650,450)) {
    std::cout << "Started\n";
    wxStaticText *text = new wxStaticText(this, wxID_ANY, "Welcome to the Home Screen!", wxPoint(100, 100));
    this->SetBackgroundColour(Settings::getInstance().colors.surface);
    text->SetForegroundColour(wxColor(255,255,255));
}
