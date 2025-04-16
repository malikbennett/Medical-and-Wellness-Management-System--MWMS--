// GuiHelpers.h
#pragma once
#include <wx/wx.h>

inline void AddText(wxPanel* panel, wxSizer* sizer, const wxString& label, const wxFont& font, int padding = 20) {
    wxStaticText* text = new wxStaticText(panel, wxID_ANY, label);
    text->SetFont(font);
    sizer->Add(text, 0, wxALIGN_LEFT | wxALL, padding);
}
