#pragma once
#include "canvas.h"
#include "sprite.h"

#include <wx/wx.h>

class Editor : public wxMDIChildFrame
{
public:
    Editor(wxMDIParentFrame *parent, const wxString &name);
    ~Editor();

    void SetColour(int c);
    bool Save(const wxString &filename);
    bool Open(const wxString &filename);
    bool New(int r, int c);

    void OnZoomChange(wxCommandEvent &event);
    void OnResize(wxSizeEvent &event);

private:
    Canvas *m_Canvas = nullptr;
    wxStatusBar *m_StatusBar = nullptr;
    wxSlider *m_ZoomSlider = nullptr;
    wxButton *m_CurrentColour = nullptr;
    olc::olcSprite sprBase;
    unsigned char *m_Sprite = nullptr;
    wxBoxSizer *m_MainSizer = nullptr;
};
