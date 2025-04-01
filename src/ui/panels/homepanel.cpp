#include "homepanel.h"

HomePanel::HomePanel(wxWindow* parent) : wxPanel(parent) {
    new wxStaticText(this, wxID_ANY, "Welcome to the Home Screen!", wxPoint(100, 100));
}
