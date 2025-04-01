// This is the main file for UI components; initialize panels (Different Screens (eg. Login, Home Page, etc..)), and different elements.

#include <MainFrame.h>
#include <User.h>
#include <Role.h>
#include <iostream>

// Inlcudes Panels

#include <LoginPanel.h>
#include <HomePanel.h>

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title){
    new LoginPanel(this);
}
