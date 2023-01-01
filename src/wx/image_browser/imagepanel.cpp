#include "imagepanel.h"

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

wxDEFINE_EVENT(IMAGE_SELECTED, wxCommandEvent);

ImagePanel::ImagePanel(wxWindow *parent, wxString file, wxBitmapType format, const wxSize &size, long style)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, size, style)
{
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);

    m_Image.LoadFile(file, format);
    m_ImageWidth = -1;
    m_ImageHeight = -1;
    fs::path p{file.ToStdString()};
    m_ImageName = p.filename().string();

    Bind(wxEVT_PAINT, &ImagePanel::OnPaint, this);
    Bind(wxEVT_SIZE, &ImagePanel::OnSize, this);
    Bind(wxEVT_LEFT_DOWN, &ImagePanel::OnMouseDown, this);
    Bind(wxEVT_KEY_DOWN, &ImagePanel::OnKeyDown, this);
}

void ImagePanel::OnPaint(wxPaintEvent &evt)
{
    wxAutoBufferedPaintDC dc(this);
    RenderImage(dc);
}

void ImagePanel::OnSize(wxSizeEvent &event)
{
    // std::cout << "Window resizing..." << std::endl;
    Refresh();
    event.Skip();
}

void ImagePanel::RenderImage(wxAutoBufferedPaintDC &dc)
{
    dc.Clear();
    wxGraphicsContext *gc = wxGraphicsContext::Create(dc);

    if (gc)
    {
        wxDouble newWidth, newHeight;
        gc->GetSize(&newWidth, &newHeight);

        // lambda for drawing an image on dc
        auto drawBasedOnSelection = [&]()
        {
            if (!m_IsSelected)
            {
                gc->DrawBitmap(m_ResizedImage, 0, 0, newWidth, newHeight);
            }
            else
            {
                gc->DrawBitmap(m_ResizedImage, 0, 0, newWidth, newHeight);
                gc->SetBrush(*wxTRANSPARENT_BRUSH);
                gc->SetPen({*wxRED, 4});
                gc->DrawRectangle(2, 2, m_ImageWidth - 2, m_ImageHeight - 2);
            }
        };

        if (newWidth != m_ImageWidth || newHeight != m_ImageHeight)
        {
            m_ResizedImage = wxBitmap(m_Image.Scale(newWidth, newHeight /*, wxIMAGE_QUALITY_HIGH*/));
            m_ImageWidth = newWidth;
            m_ImageHeight = newHeight;
            drawBasedOnSelection();
        }
        else
        {
            drawBasedOnSelection();
        }

        gc->SetFont(*wxNORMAL_FONT, *wxWHITE);
        double textWidth, textHeight;
        gc->DrawText(m_ImageName, 5, 10);
        delete gc;
    }
}

void ImagePanel::SetSelected(bool select)
{
    m_IsSelected = select;
    Refresh();
}

bool ImagePanel::GetSelected() const
{
    return m_IsSelected;
}

void ImagePanel::SetClicked(bool click)
{
    m_IsClicked = click;
}

bool ImagePanel::GetClicked() const
{
    return m_IsClicked;
}

wxSize ImagePanel::GetImageSize() const
{
    return m_Image.GetSize();
    // wxSize s;
    // s.SetWidth(m_ImageWidth);
    // s.SetHeight(m_ImageHeight);
    // return s;
}

void ImagePanel::OnMouseDown(wxMouseEvent &event)
{
    SetFocusFromKbd();
    m_IsSelected = !m_IsSelected;
    m_IsClicked = true;
    // std::cout << "ImagePanel mouse down: " << m_ImageName << " " << m_IsSelected << std::endl;
    Refresh();
    SendImageSelectedEvent();

    // event.ResumePropagation(wxEVENT_PROPAGATE_MAX);
    // event.Skip();
}

void ImagePanel::OnKeyDown(wxKeyEvent &event)
{
    std::cout << "ImagePanel key down" << std::endl;
    event.ResumePropagation(wxEVENT_PROPAGATE_MAX);
    event.Skip();
}

void ImagePanel::OnRightClick(wxContextMenuEvent &event)
{
}

void ImagePanel::SendImageSelectedEvent()
{
    wxCommandEvent event(IMAGE_SELECTED, GetId());
    event.SetEventObject(this);
    event.SetString(m_ImageName);

    ProcessWindowEvent(event);
}
