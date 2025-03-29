// This is the main file for UI components; initialize panels (Different Screens (eg. Login, Home Page, etc..)), and different elements.

#include <mainframe.h>
#include <user.h>
#include <role.h>
#include <iostream>

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title){
    wxPanel *panel = new wxPanel(this); // Creates a wxPanel, which is basically a section that you can place elements in
    wxButton *button = new wxButton(panel, wxID_ANY, "Button", wxPoint(150, 50), wxSize(100, 25)); // Creates a wxButton, which is placed in a panel
}
