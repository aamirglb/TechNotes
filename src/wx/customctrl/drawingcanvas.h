#pragma once

#include "graphicsobject.h"
#include "wx/wx.h"

#include <list>

class DrawingCanvas : public wxWindow
{
public:
    DrawingCanvas(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size);
    virtual ~DrawingCanvas() {}

    void addRect(int width, int height, int centerX, int centerY, double angle, wxColor color, const std::string &text);

private:
    void OnPaint(wxPaintEvent &event);
    std::list<GraphicsObject> objectList;
};