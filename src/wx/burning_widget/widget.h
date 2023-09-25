#pragma once

#include <wx/wx.h>

class Widget : public wxPanel
{
public:
    Widget(wxPanel *parent, int id);
    wxPanel *m_Parent;

    void OnSize(wxSizeEvent &event);
    void OnPaint(wxPaintEvent &event);
};