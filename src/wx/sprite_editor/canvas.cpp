#include "canvas.h"
#include "utils.h"

#include <wx/dcclient.h>
#include <wx/dcmemory.h>
#include <wx/dcbuffer.h>

// clang-format off
wxBEGIN_EVENT_TABLE(Canvas, wxHVScrolledWindow)
wxEND_EVENT_TABLE()

;//clang-format on

Canvas::Canvas(wxWindow *parent)
    : wxHVScrolledWindow(parent, wxID_ANY)
{
    // SetRowColumnCount(40, 40);
    // tell wxwidget that we will paint the widget manually
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    this->Bind(wxEVT_PAINT, &Canvas::OnPaint, this);
    this->Bind(wxEVT_LEFT_DOWN, &Canvas::OnMouseLeftDown, this);
    this->Bind(wxEVT_MOTION, &Canvas::OnMouseMove, this);
}

Canvas::~Canvas()
{
}

wxCoord Canvas::OnGetRowHeight(size_t row) const
{
    return wxCoord(m_PixelSize);
}

wxCoord Canvas::OnGetColumnWidth(size_t col) const
{
    return wxCoord(m_PixelSize);
}

void Canvas::OnDraw(wxDC & dc)
{
    dc.Clear();

    wxBrush brush = dc.GetBrush();
    wxPen pen = dc.GetPen();

    wxPosition start = GetVisibleBegin();
    wxPosition end = GetVisibleEnd();

    pen.SetStyle(wxPENSTYLE_LONG_DASH);
    pen.SetColour(wxColour(200, 200, 200));
    dc.SetPen(pen);

    if(m_PixelSize <= 4)
    {
        dc.SetPen(*wxTRANSPARENT_PEN);
    }

    for(int y = start.GetRow(); y < end.GetRow(); ++y)
    {
        for(int x = start.GetCol(); x < end.GetCol(); ++x)
        {
            int colour = m_Sprite[y * this->GetColumnCount() + x];
            if(colour < 16)
            {
                brush.SetColour(Utils::palette[colour]);
                brush.SetStyle(wxBRUSHSTYLE_SOLID);
            }
            else{
                brush.SetStyle(wxBrushStyle::wxBRUSHSTYLE_CROSSDIAG_HATCH);
                brush.SetColour(wxColour(0, 0, 0));
            }
            dc.SetBrush(brush);
            dc.DrawRectangle(x*m_PixelSize, y * m_PixelSize, m_PixelSize, m_PixelSize);
        }
    }
}

void Canvas::OnPaint(wxPaintEvent & event)
{
    wxBufferedPaintDC dc(this);
    this->PrepareDC(dc);
    this->OnDraw(dc);
}

void Canvas::SetPixelSize(int n)
{
    m_PixelSize = n;
    wxVarHScrollHelper::RefreshAll();
    wxVarVScrollHelper::RefreshAll();
    Refresh();
}

void Canvas::SetSpriteData(int rows, int columns, unsigned char * sprite)
{
    m_Sprite = sprite;
    this->SetRowColumnCount(rows, columns);
}

void Canvas::SetColour(int c)
{
    m_Colour = c;
}

void Canvas::OnMouseLeftDown(wxMouseEvent & event)
{
    wxPosition s = GetVisibleBegin();
    m_Sprite[ (event.GetY() / m_PixelSize + s.GetRow()) * this->GetColumnCount() + (event.GetX() / m_PixelSize + s.GetCol())] = m_Colour;
    this->Refresh(false);
    event.Skip();
}

void Canvas::OnMouseMove(wxMouseEvent & event)
{
    if(wxGetKeyState(WXK_CONTROL))
    {
        wxPosition s = GetVisibleBegin();
    m_Sprite[ (event.GetY() / m_PixelSize + s.GetRow()) * this->GetColumnCount() + (event.GetX() / m_PixelSize + s.GetCol())] = m_Colour;
    this->Refresh(false);
    event.Skip();
    }
}
