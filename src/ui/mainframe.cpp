// This is the main file for UI components; initialize panels (Different Screens (eg. Login, Home Page, etc..)), and different elements.

#include <mainframe.h>
#include <user.h>
#include <role.h>
#include <iostream>

// Inlcudes Panels

#include <loginpanel.h>
#include <homepanel.h>

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title){
    new LoginPanel(this);
}
