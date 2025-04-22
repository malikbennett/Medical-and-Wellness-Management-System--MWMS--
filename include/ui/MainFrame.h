#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>

class Footer;
class Menu;

// Main Frame class which inherits from the wxFrame class; provides main window
class MainFrame : public wxFrame
{
public:
    // MainFrame's constructor, this intializes the window and its attributes
    MainFrame(const wxString &title);
    void SwitchPanel(wxPanel* panel);
    void SetCenteredView(wxPanel *panel);

private:
    wxPanel* mainPanel;
    wxBoxSizer* mainSizer;
    wxPanel *currentView;
    Footer *footerPanel;
    Menu *menuPanel;
    wxBoxSizer *sizerCurrent;
    wxBoxSizer *sizerCenter;
};
#endif
