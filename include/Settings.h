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
  string getBackgroundColor(bool FORMAT) const { return (FORMAT) ? this->backgroundColorRGB : this->backgroundColorHEX; }
  /*returns text color*/
  string getTextColor(bool FORMAT) const { return (FORMAT) ? this->textColorRGB : this->textColorHEX; }
  /*returns primary color*/
  string getPrimaryColor(bool FORMAT) const { return (FORMAT) ? this->primaryColorRGB : this->primaryColorHEX; }
  /*returns secondary color*/
  string getSecondaryColor(bool FORMAT) const { return (FORMAT) ? this->secondaryColorRGB : this->secondaryColorHEX; }

private:
  // Private constructer; no instances can be made
  Settings(){};

  // Settings data

  string windowTitle = "MWMS";
  int windowWidth = 1280;
  int windowHeight = 720;
  string backgroundColorHEX = "#FFFCE8";
  string backgroundColorRGB = "255,252,232";
  string textColorHEX = "#25283D";
  string textColorRGB = "37,40,61";
  string primaryColorHEX = "#7180B9";
  string primaryColorRGB = "113,128,185";
  string secondaryColorHEX = "#32965D";
  string secondaryColorRGB = "50,150,93";

};
