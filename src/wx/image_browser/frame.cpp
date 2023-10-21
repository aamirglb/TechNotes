#include "frame.h"
#include "imagepanel.h"

#include <filesystem>
#include <vector>
#include <string>
#include <set>
#include <iostream>

namespace fs = std::filesystem;

static const char *None_xpm[] = {
    "32 32 2 1",
    " 	c None",
    ".	c #3A3A3A",
    "......                    ......",
    "......                    ......",
    "..                            ..",
    "..                            ..",
    "..                            ..",
    "..                            ..",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "..                            ..",
    "..                            ..",
    "..                            ..",
    "..                            ..",
    "......                    ......",
    "......                    ......"};

static char *open_xpm[] = {
    /* columns rows colors chars-per-pixel */
    "16 15 5 1",
    "  c None",
    ". c Red",
    "X c Yellow",
    "o c Gray100",
    "O c #bfbf00",
    /* pixels */
    "                ",
    "          ...   ",
    "           . . .",
    "              ..",
    " ...         ...",
    " .XoX.......    ",
    " .oXoXoXoXo.    ",
    " .XoXoXoXoX.    ",
    " .oXoX..........",
    " .XoX.OOOOOOOOO.",
    " .oo.OOOOOOOOO. ",
    " .X.OOOOOOOOO.  ",
    " ..OOOOOOOOO.   ",
    " ...........    ",
    "                "};

static const char *TEST_XPM[] = {
    "48 4 2 1",
    "a c #FFFFFF",
    "b c #000000",
    "abaabaababaaabaabababaabaabaababaabaaababaabaaab",
    "abaabaababaaabaabababaabaabaababaabaaababaabaaab",
    "abaabaababaaabaabababaabaabaababaabaaababaabaaab",
    "abaabaababaaabaabababaabaabaababaabaaababaabaaab"};

// constexpr const char* get_xpm_img(int w, int h)
// {
//     char *buffer = new buffer()
// }
static const char *PLACEHOLDER_XPM[] = {
    "32 32 1 1",
    "  c Black",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                "};

Frame::Frame(const wxString &title, const wxPoint &pos, const wxSize &size, long style)
    : wxFrame(nullptr, wxID_ANY, title, pos, size, style)
{
    CreateMessagePanel();

    m_ImageList = Frame::GetImageList("C:/Users/aamir.ali/Pictures/demo-lib/thumbnail/", 20);
    m_ImageBrowser = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxSize(1000, 600) /*, wxWANTS_CHARS*/);
    // m_ImageBrowser->SetBackgroundColour(wxColor(24, 24, 24));
    // browser->Bind(wxEVT_KEY_DOWN, &Frame::OnKeyDown, this);

    m_GridSizer = new wxGridSizer(3);

    // wxBitmap testBitmap(None_xpm);
    wxBitmap testBitmap(PLACEHOLDER_XPM);
    auto testPanel = new ImagePanel(m_ImageBrowser, testBitmap);
    m_GridSizer->Add(testPanel, 1, wxEXPAND | wxALL, 5);
    m_ImagePanels.push_back(testPanel);

    // For each loaded image, create a image panel and add to sizer
    for (int i = 0; i < 3; ++i)
    {
        CreateImagePanel(m_ImageList[m_InsertedImageCount++]);
    }

    wxBoxSizer *browserSizer = new wxBoxSizer(wxVERTICAL);
    browserSizer->Add(m_GridSizer);
    browserSizer->AddStretchSpacer(1);
    m_ImageBrowser->SetSizer(browserSizer);
    m_ImageBrowser->SetScrollRate(5, 5);

    m_AddImageButton = new wxButton(this, INSERT_IMAGE_BUTTON_ID, "Insert Image", wxDefaultPosition, wxSize(120, 24));

    // clang-format off
    m_AddImageButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&)
    { 
        if (m_InsertedImageCount < m_ImageList.size())
            CreateImagePanel(m_ImageList[m_InsertedImageCount++]);
    });
    // clang-format on

    // Bind(wxEVT_LEFT_DOWN, &Frame::OnMouseDown, this);
    Bind(wxEVT_KEY_DOWN, &Frame::OnKeyDown, this);

    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(m_ImageBrowser, 0, wxALL, 4);
    mainSizer->AddStretchSpacer(1);
    mainSizer->Add(m_AddImageButton, 0, wxLEFT, 4);

    mainSizer->Add(m_MessagePanel, 1, wxEXPAND | wxALL, 4);
    SetSizer(mainSizer);
    Layout();

    Layout();
}

void Frame::CreateMessagePanel()
{
    m_MessagePanel = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
    m_MessagePanel->SetBackgroundColour(wxColor(64, 64, 64));

    wxListItem col0;
    col0.SetId(0);
    col0.SetText(_("Message Console"));
    col0.SetWidth(GetSize().GetWidth() - 40);
    col0.SetBackgroundColour(*wxRED);
    m_MessagePanel->InsertColumn(0, col0);
}

void Frame::CreateImagePanel(const std::string &image)
{
    wxBitmapType imageType;
    // get image type
    fs::path path{image};
    if (path.extension() == ".jpg" || path.extension() == ".jpeg")
    {
        imageType = wxBITMAP_TYPE_JPEG;
    }
    else if (path.extension() == ".png")
    {
        imageType = wxBITMAP_TYPE_PNG;
    }

    auto panel = new ImagePanel(m_ImageBrowser, image, wxBITMAP_TYPE_JPEG, GetImageSize(image, imageType));
    panel->Bind(IMAGE_SELECTION_CHANGED, &Frame::OnImageSelectionChange, this);
    panel->Bind(IMAGE_DOUBLE_CLICKED, &Frame::OnImageDoubleClick, this);

    auto imageWidth = panel->GetImageSize().GetWidth();
    auto frameWidth = this->GetSize().GetWidth();

    auto colCount = frameWidth / (imageWidth + 10);
    m_GridSizer->SetCols(colCount);

    m_GridSizer->Add(panel, 1, wxEXPAND | wxALL, 5);
    m_ImagePanels.push_back(panel);

    this->Layout();

    if (m_InsertedImageCount == m_ImageList.size())
        m_AddImageButton->Disable();
}

void Frame::OnKeyDown(wxKeyEvent &event)
{
    if (event.GetKeyCode() == WXK_RIGHT || event.GetKeyCode() == WXK_LEFT)
    {
        // get number of selected images
        int totalSelected = std::count_if(m_ImagePanels.begin(), m_ImagePanels.end(), [](const auto p)
                                          { return p->GetSelected(); });
        if (totalSelected > 1)
        {
            // clear the selection
            for (auto &pane : m_ImagePanels)
            {
                pane->SetSelected(false);
            }
            return;
        }
    }

    if (event.GetKeyCode() == WXK_RIGHT)
    {
        for (auto i = 0; i < m_ImagePanels.size() - 1; ++i)
        {
            if (m_ImagePanels[i]->GetSelected() &&
                !m_ImagePanels[i + 1]->GetSelected())
            {
                std::cout << "Selected image index: " << i << std::endl;
                m_ImagePanels[i]->SetSelected(false);
                m_ImagePanels[i + 1]->SetSelected(true);

                AddConsoleMessage("Moved RIGHT...");
                break;
            }
        }
    }

    if (event.GetKeyCode() == WXK_LEFT)
    {
        for (int i = m_ImagePanels.size() - 1; i > 0; --i)
        {
            if (m_ImagePanels[i]->GetSelected() &&
                !m_ImagePanels[i - 1]->GetSelected())
            {
                m_ImagePanels[i]->SetSelected(false);
                m_ImagePanels[i - 1]->SetSelected(true);
                AddConsoleMessage("Moved LEFT...");
                break;
            }
        }
    }
}

void Frame::OnImageSelectionChange(wxCommandEvent &event)
{
    AddConsoleMessage(event.GetString());

    // Single selection
    if (!wxGetKeyState(WXK_CONTROL))
    {
        // de-select all currently selected images
        std::for_each(m_ImagePanels.begin(), m_ImagePanels.end(), [](auto p)
                      { p->SetSelected(false); });

        m_SelectedImageIdx.clear();
        ProcessImageClickEvent();
    }
    // Multi-selection
    else
    {
        ProcessImageClickEvent();
    }
}

void Frame::AddConsoleMessage(const wxString &message)
{
    static int id{1};

    wxListItem item;
    item.SetText(message);
    item.SetId(id++);
    item.SetTextColour(*wxWHITE);
    m_MessagePanel->InsertItem(item);

    m_MessagePanel->EnsureVisible(m_MessagePanel->GetItemCount() - 1);
}

void Frame::ProcessImageClickEvent()
{
    for (int i = 0; i < m_ImagePanels.size(); ++i)
    {
        if (m_ImagePanels[i]->GetClicked())
        {
            if (m_ImagePanels[i]->GetSelected() == true)
            {
                m_ImagePanels[i]->SetSelected(false);
                m_SelectedImageIdx.erase(std::remove_if(m_SelectedImageIdx.begin(), m_SelectedImageIdx.end(), [=](auto idx)
                                                        { return idx == i; }));
            }
            else
            {
                m_ImagePanels[i]->SetSelected(true);
                m_SelectedImageIdx.push_back(i);
            }

            m_ImagePanels[i]->SetClicked(false);
        }
    }

    wxString images;
    for (const auto &idx : m_SelectedImageIdx)
    {
        images += m_ImagePanels[idx]->GetImageName() + " ";
    }
    AddConsoleMessage(wxString::Format("SELECTED Images (%zu): %s", m_SelectedImageIdx.size(), images));
}

void Frame::OnImageDoubleClick(wxCommandEvent &event)
{
    AddConsoleMessage(event.GetString());
}

void Frame::OnAddImageButtonClick(wxCommandEvent &event)
{
}

wxSize Frame::GetImageSize(const std::string &filename, wxBitmapType format)
{
    wxImage image;
    if (image.LoadFile(filename, format))
    {
        return image.GetSize();
    }
    return wxSize(0, 0);
}

std::vector<std::string> Frame::GetImageList(const std::string &path, int max_images_to_load)
{
    std::vector<std::string> images;
    std::set<std::string> extensions{
        ".jpg",
        ".jpeg",
        ".png",
    };

    fs::path p{path};
    int image_count{};
    for (const auto &entry : fs::recursive_directory_iterator(p))
    {
        if (fs::is_regular_file(entry) &&
            extensions.count(entry.path().extension().string()) > 0)
        {
            ++image_count;
            auto fn = p / entry.path().filename();
            images.push_back(fn.string());

            if (image_count >= max_images_to_load)
                break;
        }
    }

    return images;
}
