#pragma once
#include <wx/wx.h>
using namespace std;

enum Theme {
    Light,
    Dark
};

struct ColorPalette {
    wxColor background;
    wxColor surface;
    wxColor surfaceLight;

    wxColor primary;
    wxColor primaryDark;

    wxColor secondary;
    wxColor secondaryDark;

    wxColor textPrimaryLight;
    wxColor textPrimary;
    wxColor textPrimaryDark;

    wxColor textSecondaryLight;
    wxColor textSecondary;
    wxColor textSecondaryDark;

    wxColor error;
};

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

  // Constant Settings Data ; these cannot be changed elsewhere
  const string windowTitle = "MWMS";
  const int windowWidth = 1280;
  const int windowHeight = 720;
  ColorPalette colors;

private:
  // Private constructer; no instances can be made
  Settings() {
    this->colors = GetColorPalette(Settings::theme);
  }
  // This prevents copying
  Settings(const Settings &) = delete;
  void operator=(const Settings &) = delete;

  static Theme theme;

  ColorPalette GetColorPalette(Theme theme = Light) {
    ColorPalette palette;

    if (theme == Light) {
        palette.background = wxColor(235, 235, 235);
        palette.surface = wxColor(245, 245, 245);
        palette.surfaceLight = wxColor(255, 255, 255);

        palette.primary = wxColor(76, 175, 80);
        palette.primaryDark = wxColor(56, 142, 60);

        palette.secondary = wxColor(74, 89, 150);
        palette.secondaryDark = wxColor(61, 73, 123);

        palette.textPrimaryLight = wxColor(62, 67, 101);
        palette.textPrimary = wxColor(37, 40, 61);
        palette.textPrimaryDark = wxColor(23, 25, 38);

        palette.textSecondaryLight = wxColor(230, 230, 230);
        palette.textSecondary = wxColor(200, 200, 200);
        palette.textSecondaryDark = wxColor(50, 50, 50);

        palette.error = wxColor(255, 80, 80);
    } else {
        palette.background = wxColor(18, 18, 18);
        palette.surface = wxColor(28, 28, 30);
        palette.surfaceLight = wxColor(38, 38, 40);

        palette.primary = wxColor(76, 175, 80);
        palette.primaryDark = wxColor(56, 142, 60);

        palette.secondary = wxColor(120, 135, 200);
        palette.secondaryDark = wxColor(90, 105, 170);

        palette.textPrimaryLight = wxColor(200, 200, 200);
        palette.textPrimary = wxColor(220, 220, 220);
        palette.textPrimaryDark = wxColor(255, 255, 255);

        palette.textSecondaryLight = wxColor(100, 100, 100);
        palette.textSecondary = wxColor(95, 95, 95);
        palette.textSecondaryDark = wxColor(70, 70, 70);

        palette.error = wxColor(255, 100, 100);
    }
    return palette;
}
};
