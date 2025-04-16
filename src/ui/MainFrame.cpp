// This is the main file for UI components; initialize panels (Different Screens (eg. Login, Home Page, etc..)), and different elements.

#include <MainFrame.h>
#include <HomePanel.h>
#include <User.h>
#include <Role.h>
#include <iostream>
#include <Settings.h>

MainFrame::MainFrame(const wxString &title) : wxFrame(nullptr, wxID_ANY, title)
{
    this->footerPanel = nullptr;
    this->menuPanel = nullptr;
    // Main Panel for the window/frame
    this->mainPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 100));

    this->mainSizer = new wxBoxSizer(wxVERTICAL);
    this->mainSizer->Add(this->mainPanel, 1, wxEXPAND | wxALL);

    this->currentView = new LoginPanel(this->mainPanel);

    // Center currentView
    this->sizerCurrent = new wxBoxSizer(wxVERTICAL);
    this->sizerCenter = new wxBoxSizer(wxHORIZONTAL);
    this->sizerCenter->Add(this->currentView, 0, wxALIGN_CENTER);
    this->sizerCurrent->Add(this->sizerCenter, 1, wxALIGN_CENTER);

    this->mainPanel->SetSizerAndFit(this->sizerCurrent);

    this->SetSizerAndFit(this->mainSizer);
}

void MainFrame::SwitchPanel(wxPanel *panel)
{
    // Remove and destroy previous view
    if (this->currentView)
    {
        this->sizerCenter->Detach(this->currentView);
        this->sizerCurrent->Detach(this->sizerCenter);
        this->currentView->Hide();
        this->currentView->Destroy();
        this->currentView = nullptr;
    }
    // Remove and destroy footer if it exists
    if (this->footerPanel)
    {
        this->sizerCurrent->Detach(this->footerPanel);
        this->footerPanel->Hide();
        this->footerPanel->Destroy();
        this->footerPanel = nullptr;
    }
    // Remove and destroy menu if it exists
    if (this->menuPanel)
    {
        this->sizerCurrent->Detach(this->menuPanel);
        this->menuPanel->Hide();
        this->menuPanel->Destroy();
        this->menuPanel = nullptr;
    }
    // Swap in new view
    if (LoginPanel *loginPanel = dynamic_cast<LoginPanel *>(panel))
    {
        this->currentView = panel;
        this->sizerCenter->Add(this->currentView, 0, wxALIGN_CENTER);
        this->sizerCurrent->Add(this->sizerCenter, 1, wxALIGN_CENTER);
    }
    else
    {
        this->currentView = panel;
        this->footerPanel = new Footer(this->mainPanel);
        this->menuPanel = new Menu(this->mainPanel);
        this->sizerCurrent->Add(this->menuPanel, 0, wxEXPAND | wxALL);
        this->sizerCurrent->Add(this->currentView, 1, wxEXPAND | wxALL);
        this->sizerCurrent->Add(this->footerPanel, 0, wxEXPAND | wxALL);
    }
    this->currentView->Show();
    this->mainPanel->Layout();
    this->mainPanel->Refresh();
    this->sizerCenter->Layout();
    this->sizerCurrent->Layout();

    std::cout << "Frame Swap\n";
}
