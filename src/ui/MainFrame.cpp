// This is the main file for UI components; initialize panels (Different Screens (eg. Login, Home Page, etc..)), and different elements.

#include <MainFrame.h>
#include <User.h>
#include <Role.h>
#include <iostream>
#include <Settings.h>

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title){
    // Main Panel for the window/frame
    this->mainPanel= new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200,100));
    this->mainPanel->SetBackgroundColour(Settings::getInstance().colors.background);

    this->mainSizer = new wxBoxSizer(wxVERTICAL);
    this->mainSizer->Add(mainPanel, 1,wxEXPAND | wxALL);

    this->homePanel = new HomePanel(mainPanel);
    this->loginPanel = new LoginPanel(mainPanel, homePanel);
    this->homePanel->Hide();
    this->Layout();

    this->SetSizerAndFit(mainSizer);
}

void MainFrame::TogglePanel(wxPanel* panel, bool visible){
    if(visible){
        panel->Show();
    }else{
        panel->Hide();
    }
}
