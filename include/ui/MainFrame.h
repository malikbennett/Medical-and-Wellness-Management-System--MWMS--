#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>
#include <LoginPanel.h>
#include <HomePanel.h>

// Main Frame class which inherits from the wxFrame class; provides main window
class MainFrame : public wxFrame
{
public:
    // MainFrame's constructor, this intializes the window and its attributes
    MainFrame(const wxString &title);
    static void TogglePanel(wxPanel* panel, bool visible);

private:
    wxPanel* mainPanel;
    wxBoxSizer* mainSizer;

    LoginPanel* loginPanel;
    HomePanel* homePanel;

    friend class LoginPanel;
};
#endif
