// This is the main file for UI components; initialize panels (Different Screens (eg. Login, Home Page, etc..)), and different elements.

#include <MainFrame.h>
#include <HomePanel.h>
#include <LoginPanel.h>
#include <SignupPanel.h>
#include <User.h>
#include <Role.h>
#include <iostream>
#include <Settings.h>

MainFrame::MainFrame(const wxString &title) : wxFrame(nullptr, wxID_ANY, title)
{
    this->menuPanel = nullptr;
    // Main Panel for the window/frame
    this->mainPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 100));

    this->mainSizer = new wxBoxSizer(wxVERTICAL);
    this->mainSizer->Add(this->mainPanel, 1, wxEXPAND | wxALL);

    this->sizerCurrent = new wxBoxSizer(wxVERTICAL);
    this->sizerCenter = new wxBoxSizer(wxHORIZONTAL);


    this->currentView = new LoginPanel(this->mainPanel);
    this->sizerCenter->Add(this->currentView, 0, wxALIGN_CENTER);
    this->sizerCurrent->Add(this->sizerCenter, 1, wxALIGN_CENTER);
    this->footerPanel = new Footer(this->mainPanel);
    this->sizerCurrent->Add(this->footerPanel, 0, wxEXPAND | wxALL);

    this->mainPanel->SetSizerAndFit(this->sizerCurrent);

    this->SetSizerAndFit(this->mainSizer);
}

void MainFrame::SetCenteredView(wxPanel *panel)
{
    this->currentView = panel;
    this->sizerCenter->Add(this->currentView, 0, wxALIGN_CENTER);
    this->sizerCurrent->Add(this->sizerCenter, 1, wxALIGN_CENTER);
}

void MainFrame::SwitchPanel(wxPanel *panel)
{
    if (this->currentView)
    {
        this->sizerCenter->Detach(this->currentView);
        this->sizerCurrent->Detach(this->sizerCenter);
        this->currentView->Hide();
        this->currentView->Destroy();
        this->currentView = nullptr;
    }

    if (this->menuPanel)
    {
        this->sizerCurrent->Detach(this->menuPanel);
        this->menuPanel->Hide();
        this->menuPanel->Destroy();
        this->menuPanel = nullptr;
    }

    this->sizerCurrent->Detach(this->footerPanel);

    if (LoginPanel *loginPanel = dynamic_cast<LoginPanel *>(panel))
    {
        SetCenteredView(panel);
        this->footerPanel->SetState(FooterState::LOGIN);
    }
    else if (SignupPanel *signupPanel = dynamic_cast<SignupPanel *>(panel))
    {
        this->currentView = panel;
        this->sizerCurrent->Add(this->currentView, 1, wxEXPAND | wxALIGN_CENTER | wxALL, 32);
        this->footerPanel->SetState(FooterState::SIGNUP);
    }
    else if (Dashboard *dashboard = dynamic_cast<Dashboard *>(panel))
    {
        this->currentView = panel;
        this->menuPanel = new Menu(this->mainPanel);
        this->sizerCurrent->Add(this->menuPanel, 0, wxEXPAND | wxALL);
        this->sizerCurrent->Add(this->currentView, 1, wxEXPAND | wxALL);
        this->footerPanel->SetState(FooterState::DASHBOARD);
    }

    this->sizerCurrent->Add(this->footerPanel, 0, wxEXPAND | wxALL);
    this->currentView->Show();
    this->mainPanel->Layout();
    this->mainPanel->Refresh();
    this->sizerCenter->Layout();
    this->sizerCurrent->Layout();
}
