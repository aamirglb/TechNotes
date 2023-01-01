#include "wx/wx.h"
#include "wx/listctrl.h"

class ImagePanel;

class Frame : public wxFrame
{
public:
    Frame(const wxString &title, const wxPoint &pos, const wxSize &size, long style = wxDEFAULT_FRAME_STYLE);
    void CreateMessagePanel();

    void OnMouseDown(wxMouseEvent &event);
    void OnKeyDown(wxKeyEvent &event);

    void OnImageSelected(wxCommandEvent &event);
    void AddConsoleMessage(const wxString &message);
    static std::vector<std::string> GetImageList(const std::string &path, int max_images_to_load = 20);

private:
    wxListCtrl *m_MessagePanel;
    wxGridSizer *m_GridSizer;
    std::vector<std::string> m_ImageList;
    std::vector<ImagePanel *> m_ImagePanels;
};