#pragma once

#include <wx/wx.h>

enum type{
    TEXT_HEADING = 0,
    TEXT_PARAGRAPH = 1,
};

class RenderText{
public:
    static RenderText &getInstance(){
        static RenderText instance;
        return instance;
    }

    wxStaticText *createText(wxPanel *parent, const wxString &label = " ", type textType = TEXT_PARAGRAPH, long style = 0L);
private:
    // Private constructer; no instances can be made
    RenderText();

    // This prevents copying
    RenderText(const RenderText &) = delete;
    void operator=(const RenderText &) = delete;

    wxFont headingFont;
    wxFont paragraphFont;
};
