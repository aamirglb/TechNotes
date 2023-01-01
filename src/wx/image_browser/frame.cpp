#include "frame.h"
#include "imagepanel.h"

#include <filesystem>
#include <vector>
#include <string>
#include <set>
#include <iostream>

namespace fs = std::filesystem;

Frame::Frame(const wxString &title, const wxPoint &pos, const wxSize &size, long style)
    : wxFrame(nullptr, wxID_ANY, title, pos, size, style)
{
    CreateMessagePanel();

    m_ImageList = Frame::GetImageList("C:/Users/aamir.ali/Pictures/demo-lib/thumbnail/", 20);
    wxScrolledWindow *browser = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxSize(1000, 600) /*, wxWANTS_CHARS*/);
    // browser->Bind(wxEVT_KEY_DOWN, &Frame::OnKeyDown, this);

    m_GridSizer = new wxGridSizer(3);
    // For each loaded image, create a image panel and add to sizer
    for (const auto &image : m_ImageList)
    {
        auto panel = new ImagePanel(browser, image, wxBITMAP_TYPE_JPEG, wxSize(300, 400));
        panel->Bind(IMAGE_SELECTED, &Frame::OnImageSelected, this);

        auto imageWidth = panel->GetImageSize().GetWidth();
        auto frameWidth = this->GetSize().GetWidth();

        auto colCount = frameWidth / (imageWidth + 10);
        // std::cout << "Column Count: " << colCount << " Frame: " << frameWidth << " image width: " << size << std::endl;
        m_GridSizer->SetCols(colCount);

        m_GridSizer->Add(panel, 1, wxEXPAND | wxALL, 5);
        m_ImagePanels.push_back(panel);
    }
    browser->SetSizer(m_GridSizer);
    browser->SetScrollRate(5, 5);

    Bind(wxEVT_LEFT_DOWN, &Frame::OnMouseDown, this);
    Bind(wxEVT_KEY_DOWN, &Frame::OnKeyDown, this);

    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(browser, 0, wxALL, 4);
    // mainSizer->AddStretchSpacer(1);
    mainSizer->Add(m_MessagePanel, 1, wxEXPAND | wxALL, 4);
    SetSizer(mainSizer);
    Layout();
}

void Frame::CreateMessagePanel()
{
    m_MessagePanel = new wxListCtrl(this, 4'001, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
    m_MessagePanel->SetBackgroundColour(wxColor(64, 64, 64));

    wxListItem col0;
    col0.SetId(0);
    col0.SetText(_("Message Console"));
    col0.SetWidth(GetSize().GetWidth() - 40);
    col0.SetBackgroundColour(*wxRED);
    m_MessagePanel->InsertColumn(0, col0);
}

void Frame::OnMouseDown(wxMouseEvent &event)
{
    // // Single selection
    // if (!wxGetKeyState(WXK_CONTROL))
    // {
    //     // de-select all currently selected images
    //     std::for_each(m_ImagePanels.begin(), m_ImagePanels.end(), [](auto p)
    //                   { p->SetSelected(false); });

    //     for (auto &panel : m_ImagePanels)
    //     {
    //         if (panel->GetClicked())
    //         {
    //             panel->SetSelected(true);
    //             panel->SetClicked(false);
    //         }
    //     }
    // }
    // // Multi-selection
    // else
    // {
    //     for (auto &panel : m_ImagePanels)
    //     {
    //         if (panel->GetClicked())
    //         {
    //             panel->SetSelected(true);
    //             panel->SetClicked(false);
    //         }
    //     }
    // }
}

void Frame::OnKeyDown(wxKeyEvent &event)
{
    std::cout << "Frame key down" << std::endl;
    if (event.GetKeyCode() == WXK_RIGHT)
    {
        for (auto i = 0; i < m_ImagePanels.size() - 1; ++i)
        {
            if (m_ImagePanels[i]->GetSelected() &&
                !m_ImagePanels[i + i]->GetSelected())
            {
                m_ImagePanels[i]->SetSelected(false);
                m_ImagePanels[i + 1]->SetSelected(true);
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
                break;
            }
        }
    }
}

void Frame::OnImageSelected(wxCommandEvent &event)
{
    AddConsoleMessage(event.GetString());

    // Single selection
    if (!wxGetKeyState(WXK_CONTROL))
    {
        // de-select all currently selected images
        std::for_each(m_ImagePanels.begin(), m_ImagePanels.end(), [](auto p)
                      { p->SetSelected(false); });

        for (auto &panel : m_ImagePanels)
        {
            if (panel->GetClicked())
            {
                panel->SetSelected(true);
                panel->SetClicked(false);
            }
        }
    }
    // Multi-selection
    else
    {
        for (auto &panel : m_ImagePanels)
        {
            if (panel->GetClicked())
            {
                panel->SetSelected(panel->GetSelected());
                panel->SetClicked(false);
            }
        }
    }
}

void Frame::AddConsoleMessage(const wxString &message)
{
    static int id{1};

    wxListItem item;
    wxString msg;
    msg.Printf("Image %s SELECTED.", message);
    item.SetText(msg);
    item.SetId(id++);
    item.SetTextColour(*wxWHITE);
    m_MessagePanel->InsertItem(item);
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
            auto fn = p / entry.path();
            images.push_back(fn.string());

            if (image_count >= max_images_to_load)
                break;
        }
    }

    return images;
}
