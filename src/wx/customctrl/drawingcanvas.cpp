#include "drawingcanvas.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"

DrawingCanvas::DrawingCanvas(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size)
    : wxWindow(parent, id, pos, size)
{
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);
    this->Bind(wxEVT_PAINT, &DrawingCanvas::OnPaint, this);
}

void DrawingCanvas::addRect(int width, int height, int centerX, int centerY, double angle, wxColor color, const std::string &text)
{
    GraphicsObject obj{
        {-width / 2.,
         -height / 2.,
         static_cast<double>(width),
         static_cast<double>(height)},
        color,
        text,
        {}};

    obj.transform.Translate(static_cast<double>(centerX), static_cast<double>(centerY));
    obj.transform.Rotate(angle);
    this->objectList.push_back(obj);
    Refresh();
}

void DrawingCanvas::OnPaint(wxPaintEvent &event)
{
    wxAutoBufferedPaintDC dc(this);
    dc.Clear();

    wxGraphicsContext *gc = wxGraphicsContext::Create(dc);

    if (gc)
    {
        wxPoint rectOrigin = this->FromDIP(wxPoint(180, 200));
        wxSize rectSize = this->FromDIP(wxSize(100, 80));

        gc->SetBrush(*wxRED_BRUSH);
        gc->DrawRectangle(rectOrigin.x, rectOrigin.y, rectSize.GetWidth(), rectSize.GetHeight());

        gc->SetFont(*wxNORMAL_FONT, *wxWHITE);
        wxString text = "Text";
        double w, h;
        gc->GetTextExtent(text, &w, &h);

        gc->DrawText(text, rectOrigin.x + rectSize.GetWidth() / 2. - w / 2., rectOrigin.y + rectSize.GetHeight() / 2. - h / 2.);

        delete gc;
    }
    else
    {
        std::cout << "Failed to create graphics context." << std::endl;
    }
}
