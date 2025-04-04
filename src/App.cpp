// This is the main driver file that you'd normally be used to //

#include <App.h>
#include <MainFrame.h>
#include <Settings.h>
#include <User.h>
#include <Encryption.h>
#include <iostream>

// This function starts the main function (Needed for program to run)
wxIMPLEMENT_APP(App);

App::App(){}
App::~App(){}

bool App::OnInit(){
    // Get window values from settings manager

    string title = Settings::getInstance().getWindowTitle();
    int height = Settings::getInstance().getWindowHeight();
    int width = Settings::getInstance().getWindowWidth();

    // Creates an instance of a "wxFrame", which is basically a window
    MainFrame *mainFrame = new MainFrame(title);
    // Makes window visible
    mainFrame->Show(true);
    // Sets window size
    mainFrame->SetClientSize(width, height);
    // Centers window
    mainFrame->Center();

    return true;
}
