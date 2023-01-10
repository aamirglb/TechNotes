#pragma once

#include <wx/wx.h>
#include <wx/vscroll.h>

class Canvas : public wxHVScrolledWindow
{
public:
    Canvas(wxWindow *parent);
    ~Canvas();
    void SetPixelSize(int n);
    void SetSpriteData(int rows, int columns, unsigned char *sprite);
    void SetColour(int c);

    void OnMouseLeftDown(wxMouseEvent &event);
    void OnMouseMove(wxMouseEvent &event);

private:
    virtual wxCoord OnGetRowHeight(size_t row) const override;
    virtual wxCoord OnGetColumnWidth(size_t col) const override;
    void OnDraw(wxDC &dc);
    void OnPaint(wxPaintEvent &event);

    int m_PixelSize{8};
    wxDECLARE_EVENT_TABLE();
    unsigned char *m_Sprite = nullptr;
    int m_Colour{0};
};