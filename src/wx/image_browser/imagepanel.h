#include "wx/wx.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"

// declare custom event for image panel
wxDECLARE_EVENT(IMAGE_SELECTION_CHANGED, wxCommandEvent);
wxDECLARE_EVENT(IMAGE_DESELECTED, wxCommandEvent);
wxDECLARE_EVENT(IMAGE_DOUBLE_CLICKED, wxCommandEvent);
wxDECLARE_EVENT(REMOVE_SELECTED_IMAGE, wxCommandEvent);

class ImagePanel : public wxPanel
{
public:
    ImagePanel(wxWindow *parent, wxString file, wxBitmapType format, const wxSize &size = wxDefaultSize, long style = wxWANTS_CHARS);
    ImagePanel(wxWindow *parent, wxBitmap bitmap, const wxSize &size = wxDefaultSize, long style = wxWANTS_CHARS);

    void OnPaint(wxPaintEvent &evt);
    void OnSize(wxSizeEvent &event);
    void RenderImageResized(wxAutoBufferedPaintDC &dc);
    void RenderImageAsIs(wxAutoBufferedPaintDC &dc);

    void SetSelected(bool select);
    bool GetSelected() const;
    void SetClicked(bool click);
    bool GetClicked() const;
    wxSize GetImageSize() const;
    const wxString GetImageName() const;

    void OnMouseDown(wxMouseEvent &event);
    void OnDoubleClick(wxMouseEvent &event);
    void OnKeyDown(wxKeyEvent &event);
    void OnRightClick(wxContextMenuEvent &event);

    void SendImageSelectedEvent();
    void SendImageUnSelectedEvent();

private:
    wxImage m_Image;
    wxBitmap m_ResizedImage;
    wxString m_ImageName;
    wxDouble m_ImageWidth;
    wxDouble m_ImageHeight;
    bool m_IsSelected{};
    bool m_IsClicked{};
};