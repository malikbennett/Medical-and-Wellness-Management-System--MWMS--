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
  string getBackgroundColor() const { return this->backgroundColor; }
  /*returns text color*/
  string getTextColor() const { return this->textColor; }
  /*returns primary color*/
  string getPrimaryColor() const { return this->primaryColor; }
  /*returns secondary color*/
  string getSecondaryColor() const { return this->secondaryColor; }

private:
  // Private constructer; no instances can be made
  Settings(){};

  // Settings data

  string windowTitle = "MWMS";
  int windowWidth = 1280;
  int windowHeight = 720;
  string backgroundColor = "#FFFCE8";
  string textColor = "#25283D";
  string primaryColor = "#7180B9";
  string secondaryColor = "#32965D";
};
