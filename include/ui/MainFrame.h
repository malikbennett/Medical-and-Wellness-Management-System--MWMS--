#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>
#include <LoginPanel.h>

// Main Frame class which inherits from the wxFrame class; provides main window
class MainFrame : public wxFrame
{
public:
    // MainFrame's constructor, this intializes the window and its attributes
    MainFrame(const wxString &title);
    void SwitchPanel(wxPanel* panel);

private:
    wxPanel* mainPanel;
    wxBoxSizer* mainSizer;
    wxPanel *currentView;
    wxPanel *footerPanel;
    wxPanel *menuPanel;
    wxBoxSizer *sizerCurrent;
    wxBoxSizer *sizerCenter;
};
#endif
