#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>

// Main Frame class which inherits from the wxFrame class; provides main window
class MainFrame : public wxFrame
{
public:
    // MainFrame's constructor, this intializes the window and its attributes
    MainFrame(const wxString &title);
};
#endif
