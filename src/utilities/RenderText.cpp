#include <RenderText.h>
#include <Settings.h>

RenderText::RenderText(){
    this->headingFont = wxFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    this->paragraphFont = wxFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
}

wxStaticText *RenderText::createText(wxPanel *parent, const wxString &label, type textType, long style){
    wxStaticText *text = new wxStaticText(parent, wxID_ANY, label,wxDefaultPosition,wxDefaultSize, style);
    switch (textType)
    {
    case TEXT_HEADING:
        text->SetFont(this->headingFont);
        break;
        case TEXT_PARAGRAPH:
        text->SetFont(this->paragraphFont);
        break;
    default:
        break;
    }
    text->SetForegroundColour(Settings::getInstance().colors.textPrimary);
    return text;
}
