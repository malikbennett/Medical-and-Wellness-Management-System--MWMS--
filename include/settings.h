#pragma once

#include <wx/wx.h>
#include <wx/config.h>

using namespace std;

/*
Singleton class for program settings that can be access throughout codebase for things like
the window Size, Position, and other stuff
*/
class Settings {
public:
    // Returns an instance of SettingsManager which is shared throughout the codebase
    static Settings &getInstance();
    // returns window width
    int getWindowWidth() const;
    /*returns window height*/
    int getWindowHeight() const;
    /*returns window title*/
    string getWindowTitle();
    std::string getBackgroundColor() const { return backgroundColor; }
    std::string getTextColor() const { return textColor; }

private:
    // Private constructer; no instances can be made
    Settings();

    // Settings data

    string windowTitle = "MWMS";
    int windowWidth = 1280;
    int windowHeight = 720;
    string backgroundColor = "#FFFFFF";
    string textColor = "#000000";
};
