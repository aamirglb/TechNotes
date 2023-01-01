#include "drawingcanvas.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"

#include <iostream>

wxDEFINE_EVENT(CANVAS_RECT_ADDED, wxCommandEvent);
wxDEFINE_EVENT(CANVAS_RECT_REMOVED, wxCommandEvent);

DrawingCanvas::DrawingCanvas(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size)
    : wxWindow(parent, id, pos, size)
{
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);
    this->Bind(wxEVT_PAINT, &DrawingCanvas::OnPaint, this);
    this->Bind(wxEVT_LEFT_DOWN, &DrawingCanvas::OnMouseDown, this);
    this->Bind(wxEVT_MOTION, &DrawingCanvas::OnMouseMove, this);
    this->Bind(wxEVT_LEFT_UP, &DrawingCanvas::OnMouseUp, this);
    this->Bind(wxEVT_LEAVE_WINDOW, &DrawingCanvas::OnMouseLeave, this);

    // sample rectangles
    addRect(this->FromDIP(100), this->FromDIP(80), this->FromDIP(210), this->FromDIP(140), 0, *wxRED, "Rect #1");
    addRect(this->FromDIP(130), this->FromDIP(110), this->FromDIP(280), this->FromDIP(210), M_PI / 3.0, *wxBLUE, "Rect #2");
    addRect(this->FromDIP(110), this->FromDIP(110), this->FromDIP(300), this->FromDIP(120), -M_PI / 4.0, wxColor(255, 0, 255, 128), "Rect #3");

    this->draggedObj = nullptr;
    this->shouldRotate = false;

    m_timer = new wxTimer(this, 5'002);
    Bind(wxEVT_TIMER, wxTimerEventHandler(DrawingCanvas::OnTimer), this, 5'002);
    m_timer->Start(100, wxTIMER_CONTINUOUS);
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

    sendRectAddedEvent(text);
    Refresh();
}

void DrawingCanvas::removeTopRect()
{
    if (!this->objectList.empty() && draggedObj == nullptr)
    {
        auto text = this->objectList.back().text;
        this->objectList.pop_back();

        sendRectRemovedEvent(text);
        Refresh();
    }
}

void DrawingCanvas::OnTimer(wxTimerEvent &event)
{
    static double angle{1.0};
    if (wxGetKeyState(WXK_CONTROL) == true)
    {
        for (auto &obj : objectList)
        {
            obj.transform.Rotate((angle * M_PI) / 180.0);
        }
        Refresh();
        ++angle;
    }
}

void DrawingCanvas::OnPaint(wxPaintEvent &event)
{
    wxAutoBufferedPaintDC dc(this);
    dc.SetBackground(wxBrush(wxColor(64, 64, 64)));
    dc.Clear();

    wxGraphicsContext *gc = wxGraphicsContext::Create(dc);

    if (gc)
    {
        for (const auto &object : objectList)
        {
            gc->SetTransform(gc->CreateMatrix(object.transform));
            gc->SetBrush(wxBrush(object.color));
            gc->DrawRectangle(object.rect.m_x, object.rect.m_y, object.rect.m_width, object.rect.m_height);
            gc->SetFont(*wxNORMAL_FONT, *wxWHITE);

            double textWidth, textHeight;
            gc->GetTextExtent(object.text, &textWidth, &textHeight);
            gc->DrawText(object.text, object.rect.m_x + object.rect.m_width / 2.0 - textWidth / 2.0,
                         object.rect.m_y + object.rect.m_height / 2.0 - textHeight / 2.0);
        }
        delete gc;
        // wxSize rectSize = this->FromDIP(wxSize(100, 80));
        // // wxPoint rectOrigin = this->FromDIP(wxPoint(180, 200));
        // wxPoint rectOrigin = {-rectSize.GetWidth() / 2, -rectSize.GetHeight() / 2};

        // wxAffineMatrix2D transform{};
        // transform.Translate(100, 130);
        // transform.Rotate(M_PI / 3.);
        // transform.Scale(3, 3);

        // gc->SetTransform(gc->CreateMatrix(transform));

        // gc->SetBrush(*wxRED_BRUSH);
        // gc->DrawRectangle(rectOrigin.x, rectOrigin.y, rectSize.GetWidth(), rectSize.GetHeight());

        // gc->SetFont(*wxNORMAL_FONT, *wxWHITE);
        // wxString text = "Text";
        // double w, h;
        // gc->GetTextExtent(text, &w, &h);

        // gc->DrawText(text, rectOrigin.x + rectSize.GetWidth() / 2. - w / 2., rectOrigin.y + rectSize.GetHeight() / 2. - h / 2.);

        // delete gc;
    }
    else
    {
        std::cout << "Failed to create graphics context." << std::endl;
    }
}

void DrawingCanvas::OnMouseDown(wxMouseEvent &event)
{
    auto clickedObjectItr = std::find_if(objectList.rbegin(), objectList.rend(),
                                         [event](const GraphicsObject &o)
                                         {
                                             wxPoint2DDouble clickPos = event.GetPosition();
                                             auto inv = o.transform;
                                             inv.Invert();
                                             clickPos = inv.TransformPoint(clickPos);
                                             return o.rect.Contains(clickPos);
                                         });

    if (clickedObjectItr != objectList.rend())
    {
        auto forwardItr = std::prev(clickedObjectItr.base());
        objectList.push_back(*forwardItr);
        objectList.erase(forwardItr);

        draggedObj = &(*std::prev(objectList.end()));
        lastDragOrigin = event.GetPosition();
        shouldRotate = wxGetKeyState(WXK_ALT);
        Refresh();
    }
}

void DrawingCanvas::OnMouseMove(wxMouseEvent &event)
{
    if (draggedObj != nullptr)
    {
        if (shouldRotate)
        {
            double absoluteYDiff = event.GetPosition().y - lastDragOrigin.m_y;
            draggedObj->transform.Rotate(absoluteYDiff / 100.0 * M_PI);
        }
        else
        {
            auto dragVector = event.GetPosition() - lastDragOrigin;
            auto inv = draggedObj->transform;
            inv.Invert();
            dragVector = inv.TransformDistance(dragVector);
            draggedObj->transform.Translate(dragVector.m_x, dragVector.m_y);
        }

        lastDragOrigin = event.GetPosition();
        Refresh();
    }
}

void DrawingCanvas::OnMouseUp(wxMouseEvent &event)
{
    finishDrag();
    finishRotation();
}

void DrawingCanvas::OnMouseLeave(wxMouseEvent &event)
{
    finishDrag();
    finishRotation();
}

void DrawingCanvas::finishDrag()
{
    draggedObj = nullptr;
}

void DrawingCanvas::finishRotation()
{
    shouldRotate = false;
}

void DrawingCanvas::sendRectAddedEvent(const wxString &rectTitle)
{
    wxCommandEvent event(CANVAS_RECT_ADDED, GetId());
    event.SetEventObject(this);
    event.SetString(rectTitle);

    ProcessWindowEvent(event);
}

void DrawingCanvas::sendRectRemovedEvent(const wxString &rectTitle)
{
    wxCommandEvent event(CANVAS_RECT_REMOVED, GetId());
    event.SetEventObject(this);
    event.SetString(rectTitle);

    ProcessWindowEvent(event);
}
