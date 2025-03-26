#include <app.h>
#include <mainframe.h>

wxIMPLEMENT_APP(App);

bool App::OnInit(){
    MainFrame *mainFrame = new MainFrame("MWMS");
    mainFrame->Show(true);
    mainFrame->SetClientSize(1280, 720);
    mainFrame->Center();
    return true;
}
