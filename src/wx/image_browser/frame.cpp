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
        panel->Bind(IMAGE_SELECTION_CHANGED, &Frame::OnImageSelectionChange, this);
        panel->Bind(IMAGE_DOUBLE_CLICKED, &Frame::OnImageDoubleClick, this);

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
        SelectClickedImage(false);
    }
    // Multi-selection
    else
    {
        SelectClickedImage(true);
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

void Frame::SelectClickedImage(bool isMultiSelection)
{
    for (int i = 0; i < m_ImagePanels.size(); ++i)
    {
        if (m_ImagePanels[i]->GetClicked())
        {
            if (isMultiSelection)
                m_ImagePanels[i]->SetSelected(m_ImagePanels[i]->GetSelected());
            else
                m_ImagePanels[i]->SetSelected(true);
            m_ImagePanels[i]->SetClicked(false);
            m_SelectedImageIdx.push_back(i);
        }
    }
}

void Frame::OnImageDoubleClick(wxCommandEvent &event)
{
    AddConsoleMessage(event.GetString());
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
