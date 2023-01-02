#include "imagepanel.h"

#include <filesystem>
#include <iostream>
#include <exception>
#include <stdexcept>

namespace fs = std::filesystem;

wxDEFINE_EVENT(IMAGE_SELECTION_CHANGED, wxCommandEvent);
wxDEFINE_EVENT(IMAGE_DESELECTED, wxCommandEvent);
wxDEFINE_EVENT(IMAGE_DOUBLE_CLICKED, wxCommandEvent);

ImagePanel::ImagePanel(wxWindow *parent, wxString file, wxBitmapType format, const wxSize &size, long style)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, size, style)
{
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);

    if (!m_Image.LoadFile(file, format))
    {
        std::string msg = "File '" + std::string(file.mb_str()) + "' not found.";
        throw std::invalid_argument(msg);
    }

    auto [w, h] = m_Image.GetSize();
    this->SetSize(w, h);

    m_ImageWidth = -1;
    m_ImageHeight = -1;
    fs::path p{file.ToStdString()};
    m_ImageName = p.filename().string();

    Bind(wxEVT_PAINT, &ImagePanel::OnPaint, this);
    Bind(wxEVT_SIZE, &ImagePanel::OnSize, this);
    Bind(wxEVT_LEFT_DOWN, &ImagePanel::OnMouseDown, this);
    Bind(wxEVT_LEFT_DCLICK, &ImagePanel::OnDoubleClick, this);
    Bind(wxEVT_KEY_DOWN, &ImagePanel::OnKeyDown, this);

    SetFocusFromKbd();
}

void ImagePanel::OnPaint(wxPaintEvent &evt)
{
    wxAutoBufferedPaintDC dc(this);
    // RenderImageResized(dc);
    RenderImageAsIs(dc);
}

void ImagePanel::OnSize(wxSizeEvent &event)
{
    Refresh();
    event.Skip();
}

void ImagePanel::RenderImageResized(wxAutoBufferedPaintDC &dc)
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

                SetFocusFromKbd();
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

void ImagePanel::RenderImageAsIs(wxAutoBufferedPaintDC &dc)
{
    dc.Clear();
    wxGraphicsContext *gc = wxGraphicsContext::Create(dc);

    if (gc)
    {
        auto [imageWidth, imageHeight] = m_Image.GetSize();

        if (!m_IsSelected)
        {
            gc->DrawBitmap(m_Image, 0, 0, imageWidth, imageHeight);
        }
        else
        {
            auto [panelWidth, panelHeight] = this->GetSize();
            gc->DrawBitmap(m_Image, 0, 0, imageWidth, imageHeight);
            gc->SetBrush(*wxTRANSPARENT_BRUSH);
            gc->SetPen({*wxRED, 4});
            // gc->DrawRectangle(2, 2, panelWidth - 2, panelHeight - 2);
            gc->DrawRectangle(2, 2, imageWidth - 2, imageHeight - 2);

            SetFocusFromKbd();
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

    // if (m_IsSelected == true)
    //     SendImageSelectedEvent();
    // else
    //     SendImageUnSelectedEvent();
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

const wxString ImagePanel::GetImageName() const
{
    return m_ImageName;
}

void ImagePanel::OnMouseDown(wxMouseEvent &event)
{
    // m_IsSelected = !m_IsSelected;
    m_IsClicked = true;
    // std::cout << "ImagePanel mouse down: " << m_ImageName << " " << m_IsSelected << std::endl;
    Refresh();

    SendImageSelectedEvent();

    // if (m_IsSelected == false)
    //     SendImageSelectedEvent();
    // else
    //     SendImageUnSelectedEvent();

    // event.ResumePropagation(wxEVENT_PROPAGATE_MAX);
    // event.Skip();
}

void ImagePanel::OnDoubleClick(wxMouseEvent &event)
{
    wxString msg;
    msg.Printf("Image %s DOUBLE CLICKED", m_ImageName);

    wxCommandEvent e(IMAGE_DOUBLE_CLICKED, GetId());
    e.SetEventObject(this);
    e.SetString(msg);
    ProcessWindowEvent(e);
}

void ImagePanel::OnKeyDown(wxKeyEvent &event)
{
    event.ResumePropagation(wxEVENT_PROPAGATE_MAX);
    event.Skip();
}

void ImagePanel::OnRightClick(wxContextMenuEvent &event)
{
}

void ImagePanel::SendImageSelectedEvent()
{
    wxString msg;
    msg.Printf("Image %s CLICKED.", m_ImageName);

    wxCommandEvent event(IMAGE_SELECTION_CHANGED, GetId());
    event.SetEventObject(this);
    event.SetString(msg);

    ProcessWindowEvent(event);
}

void ImagePanel::SendImageUnSelectedEvent()
{
    wxString msg;
    msg.Printf("Image %s DESELECTED.", m_ImageName);

    wxCommandEvent event(IMAGE_DESELECTED, GetId());
    event.SetEventObject(this);
    event.SetString(msg);

    ProcessWindowEvent(event);
}
