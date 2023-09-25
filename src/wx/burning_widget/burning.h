#pragma once

#include <wx/wx.h>
#include "widget.h"

class Burning : public wxFrame
{
public:
    Burning(const wxString &title);
    void OnScroll(wxScrollEvent &event);
    int GetCurWidth();

    wxSlider *m_Slider;
    Widget *m_Widget;
    int m_CurWidth;
};
