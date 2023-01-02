#include "wx/wx.h"
#include "wx/listctrl.h"

class ImagePanel;

class Frame : public wxFrame
{
public:
    enum
    {
        INSERT_IMAGE_BUTTON_ID = 5'001,
    };

    Frame(const wxString &title, const wxPoint &pos, const wxSize &size, long style = wxDEFAULT_FRAME_STYLE);
    void CreateMessagePanel();
    void CreateImagePanel(const std::string &image);

    void OnKeyDown(wxKeyEvent &event);

    void OnImageSelectionChange(wxCommandEvent &event);
    void AddConsoleMessage(const wxString &message);
    void ProcessImageClickEvent();
    void OnImageDoubleClick(wxCommandEvent &event);
    void OnAddImageButtonClick(wxCommandEvent &event);
    wxSize GetImageSize(const std::string &filename, wxBitmapType format);

    static std::vector<std::string> GetImageList(const std::string &path, int max_images_to_load = 20);

private:
    int m_InsertedImageCount{};
    wxListCtrl *m_MessagePanel;
    wxGridSizer *m_GridSizer;
    wxButton *m_AddImageButton;
    wxScrolledWindow *m_ImageBrowser;

    std::vector<std::string> m_ImageList;
    std::vector<ImagePanel *> m_ImagePanels;
    std::vector<int> m_SelectedImageIdx;
};