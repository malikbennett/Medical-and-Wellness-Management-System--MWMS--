#include <settings.h>

Settings::Settings(){}

Settings &Settings::getInstance()
{
  // An instance which belongs to the class itself
  static Settings instance;
  return instance;
}
int Settings::getWindowWidth() const
{
  return this->windowWidth;
}
int Settings::getWindowHeight() const
{
  return this->windowHeight;
}
string Settings::getWindowTitle()
{
  return this->windowTitle;
}
