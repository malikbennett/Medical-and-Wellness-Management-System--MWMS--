#pragma once

#include <wx/wx.h>

using namespace std;

/*
Singleton class for program settings that can be access throughout codebase for things like
the window Size, Position, and other stuff
*/
class Settings
{
public:
  // Returns an instance of SettingsManager which is shared throughout the codebase
  static Settings &getInstance()
  {
    static Settings instance;
    return instance;
  };
  // returns window width
  int getWindowWidth() const { return this->windowWidth; };
  /*returns window height*/
  int getWindowHeight() const { return this->windowHeight; };
  /*returns window title*/
  string getWindowTitle() { return this->windowTitle; };
  /*returns window background color*/
  wxColor &getBackgroundColor(bool FORMAT) const { return *this->backgroundColor; }
  /*returns text color*/
  wxColor &getTextColor(bool FORMAT) const { return *this->textColor; }
  /*returns primary color*/
  wxColor &getPrimaryColor(bool FORMAT) const { return *this->primaryColor; }
  /*returns secondary color*/
  wxColor &getSecondaryColor(bool FORMAT) const { return *this->secondaryColor; }

private:
  // Private constructer; no instances can be made
  Settings(){};

  // Settings data

  string windowTitle = "MWMS";
  int windowWidth = 1280;
  int windowHeight = 720;
  wxColor* backgroundColor = new wxColor(255,252,232);
  wxColor* textColor = new wxColor( 37,40,61);
  wxColor* primaryColor = new wxColor(113,128,185);
  wxColor* secondaryColor = new wxColor(50,150,93);
};
