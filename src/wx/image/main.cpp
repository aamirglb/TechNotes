#include "wx/wx.h"
#include "wx/sizer.h"
#include "wx/utils.h"

#include <wx/wx.h>
#include <wx/sizer.h>

#include <vector>
#include <set>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

std::vector<std::string> getImageList(const std::string &path)
{
    int max_image_count{20};
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
            std::cout << images.back() << std::endl;
            if (image_count >= max_image_count)
                break;
        }
    }

    return images;
}

class wxImagePanel : public wxPanel
{
    wxImage image;
    wxBitmap resized;
    wxString imageName;
    int w, h;
    bool isSelected{};
    bool isClicked{};
    wxMenu *contextMenu = nullptr;

public:
    wxImagePanel(wxFrame *parent, wxString file, wxBitmapType format, const wxSize &size = wxDefaultSize, long style = wxWANTS_CHARS);

    void paintEvent(wxPaintEvent &evt);
    void paintNow();
    void OnSize(wxSizeEvent &event);
    void render(wxDC &dc);
    void setSelected(bool select)
    {
        isSelected = select;
        Refresh();
    }
    bool getSelected() const { return isSelected; }
    void setClicked(bool click) { isClicked = click; }
    bool getClicked() const { return isClicked; }

    void mouseDown(wxMouseEvent &event);
    void OnKeyDown(wxKeyEvent &event);
    void OnRightClick(wxContextMenuEvent &event);

    // some useful events
    /*
     void mouseMoved(wxMouseEvent& event);
     void mouseDown(wxMouseEvent& event);
     void mouseWheelMoved(wxMouseEvent& event);
     void mouseReleased(wxMouseEvent& event);
     void rightClick(wxMouseEvent& event);
     void mouseLeftWindow(wxMouseEvent& event);
     void keyPressed(wxKeyEvent& event);
     void keyReleased(wxKeyEvent& event);
     */

    DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(wxImagePanel, wxPanel)
// some useful events
/*
 EVT_MOTION(wxImagePanel::mouseMoved)
 EVT_LEFT_DOWN(wxImagePanel::mouseDown)
 EVT_LEFT_UP(wxImagePanel::mouseReleased)
 EVT_RIGHT_DOWN(wxImagePanel::rightClick)
 EVT_LEAVE_WINDOW(wxImagePanel::mouseLeftWindow)
 EVT_KEY_DOWN(wxImagePanel::keyPressed)
 EVT_KEY_UP(wxImagePanel::keyReleased)
 EVT_MOUSEWHEEL(wxImagePanel::mouseWheelMoved)
 */

// catch paint events
EVT_PAINT(wxImagePanel::paintEvent)
// Size event
EVT_SIZE(wxImagePanel::OnSize)
// Mouse Release
EVT_LEFT_DOWN(wxImagePanel::mouseDown)
EVT_KEY_DOWN(wxImagePanel::OnKeyDown)
EVT_CONTEXT_MENU(wxImagePanel::OnRightClick)
END_EVENT_TABLE()

// some useful events
/*
 void wxImagePanel::mouseMoved(wxMouseEvent& event) {}
 void wxImagePanel::mouseDown(wxMouseEvent& event) {}
 void wxImagePanel::mouseWheelMoved(wxMouseEvent& event) {}
 void wxImagePanel::mouseReleased(wxMouseEvent& event) {}
 void wxImagePanel::rightClick(wxMouseEvent& event) {}
 void wxImagePanel::mouseLeftWindow(wxMouseEvent& event) {}
 void wxImagePanel::keyPressed(wxKeyEvent& event) {}
 void wxImagePanel::keyReleased(wxKeyEvent& event) {}
 */

wxImagePanel::wxImagePanel(wxFrame *parent, wxString file, wxBitmapType format, const wxSize &size, long style)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, size, style)
{
    // parent = parent;
    // load the file... ideally add a check to see if loading was successful
    image.LoadFile(file, format);
    w = -1;
    h = -1;
    fs::path p{file.ToStdString()};
    imageName = p.filename().string();

    // contextMenu = new wxMenu;
    // contextMenu->Append(10'001, wxT("Remove Image"));
}

/*
 * Called by the system of by wxWidgets when the panel needs
 * to be redrawn. You can also trigger this call by
 * calling Refresh()/Update().
 */

void wxImagePanel::paintEvent(wxPaintEvent &evt)
{
    // depending on your system you may need to look at double-buffered dcs
    wxPaintDC dc(this);
    render(dc);
}

/*
 * Alternatively, you can use a clientDC to paint on the panel
 * at any time. Using this generally does not free you from
 * catching paint events, since it is possible that e.g. the window
 * manager throws away your drawing when the window comes to the
 * background, and expects you will redraw it when the window comes
 * back (by sending a paint event).
 */
void wxImagePanel::paintNow()
{
    // depending on your system you may need to look at double-buffered dcs
    wxClientDC dc(this);
    render(dc);
}

/*
 * Here we do the actual rendering. I put it in a separate
 * method so that it can work no matter what type of DC
 * (e.g. wxPaintDC or wxClientDC) is used.
 */
void wxImagePanel::render(wxDC &dc)
{
    int neww, newh;
    dc.GetSize(&neww, &newh);

    auto drawBaseOnSelection = [&]()
    {
        if (!isSelected)
        {
            dc.DrawBitmap(resized, 0, 0, false);
        }
        else
        {
            dc.DrawBitmap(resized, 0, 0, false);
            dc.SetBrush(*wxTRANSPARENT_BRUSH);
            wxPen pen(*wxYELLOW, 4 /*, wxPENSTYLE_LONG_DASH*/);
            dc.SetPen(pen);
            dc.DrawRectangle(2, 2, w - 2, h - 2);
        }
    };

    if (neww != w || newh != h)
    {
        resized = wxBitmap(image.Scale(neww, newh /*, wxIMAGE_QUALITY_HIGH*/));
        w = neww;
        h = newh;
        drawBaseOnSelection();
    }
    else
    {
        drawBaseOnSelection();
    }

    dc.SetFont(*wxNORMAL_FONT);
    wxCoord tx, ty;
    dc.GetTextExtent(imageName, &tx, &ty);

    dc.DrawText(imageName, 10, 10);
    // dc.DrawText("Image", 0, h + 4);
}

/*
 * Here we call refresh to tell the panel to draw itself again.
 * So when the user resizes the image panel the image should be resized too.
 */
void wxImagePanel::OnSize(wxSizeEvent &event)
{
    Refresh();
    // skip the event.
    event.Skip();
}

void wxImagePanel::mouseDown(wxMouseEvent &event)
{
    // parent->deSelectAll();
    isSelected = !isSelected;
    isClicked = true;
    Refresh();
    std::cout << "Image '" << imageName << "' clicked" << std::endl;
    event.ResumePropagation(wxEVENT_PROPAGATE_MAX);
    event.Skip();
}

void wxImagePanel::OnKeyDown(wxKeyEvent &event)
{
    std::cout << __FUNCTION__ << std::endl;
    event.ResumePropagation(wxEVENT_PROPAGATE_MAX);
    event.Skip();
}

void wxImagePanel::OnRightClick(wxContextMenuEvent &event)
{
    // if (isSelected)
    // {
    //     PopupMenu(contextMenu);
    //     // this->Destroy();
    //     event.ResumePropagation(wxEVENT_PROPAGATE_MAX);
    //     // event.Skip();
    // }
}

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size, long style = wxDEFAULT_FRAME_STYLE);
    void addImage(const std::string &image);
    void mouseDown(wxMouseEvent &event);
    void deSelectAll();
    void onAddImageButtonClick(wxCommandEvent &event);
    void OnKeyDown(wxKeyEvent &event);
    void OnRightClick(wxContextMenuEvent &event);

private:
    std::vector<wxImagePanel *> drawPanes;
    wxGridSizer *sizer;
    wxBoxSizer *mainSizer;
    wxButton *addImageButton;
    std::vector<std::string> images;
    int imageCount{};
};

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size, long style)
    : wxFrame(nullptr, wxID_ANY, title, pos, size, style)
{
    sizer = new wxGridSizer(3);

    images = getImageList("C:/Users/aamir.ali/Pictures/demo-lib/thumbnail/");
    for (const auto &image : images)
    {
        auto drawPane = new wxImagePanel(this, image, wxBITMAP_TYPE_JPEG, wxSize(300, 400));
        sizer->Add(drawPane, 1, wxEXPAND | wxALL, 5);
        drawPanes.push_back(drawPane);
    }

    addImageButton = new wxButton(this, wxID_ANY, "Add Image", wxDefaultPosition, wxSize(120, 22));
    addImageButton->Bind(wxEVT_BUTTON, &MyFrame::onAddImageButtonClick, this);

    this->Bind(wxEVT_LEFT_DOWN, &MyFrame::mouseDown, this);
    this->Bind(wxEVT_KEY_DOWN, &MyFrame::OnKeyDown, this);
    // this->Bind(wxEVT_CONTEXT_MENU, &MyFrame::OnRightClick, this);

    mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(addImageButton, 0, wxALIGN_LEFT | wxLEFT | wxTOP | wxBOTTOM, 5);
    mainSizer->Add(sizer, 0, wxEXPAND | wxALL, 5);
    this->SetSizer(mainSizer);
}

void MyFrame::addImage(const std::string &image)
{
    auto drawPane = new wxImagePanel(this, image, wxBITMAP_TYPE_JPEG, wxSize(300, 400));
    sizer->Add(drawPane, 0, wxEXPAND | wxALL, 5);
    // sizer->Add(drawPane, wxSizerFlags(0).Expand());
    drawPanes.push_back(drawPane);
    this->Layout();
    // sizer->Layout();
}

void MyFrame::mouseDown(wxMouseEvent &event)
{
    std::cout << __func__ << " mouse down." << std::endl;
    if (!wxGetKeyState(WXK_CONTROL))
    {
        for (auto &pane : drawPanes)
        {
            pane->setSelected(false);
        }

        for (auto &pane : drawPanes)
        {
            if (pane->getClicked())
            {
                pane->setSelected(true);
                pane->setClicked(false);
            }
        }
    }
    else
    {
        for (auto &pane : drawPanes)
        {
            if (pane->getClicked())
            {
                pane->setSelected(pane->getSelected());
                pane->setClicked(false);
            }
        }
    }

    event.Skip();
}

void MyFrame::deSelectAll()
{
    for (auto &pane : drawPanes)
    {
        pane->setSelected(false);
    }
}

void MyFrame::onAddImageButtonClick(wxCommandEvent &event)
{
    if (imageCount < images.size())
        addImage(images[imageCount++]);
}

void MyFrame::OnKeyDown(wxKeyEvent &event)
{
    // get number of selected images
    int total_selected = std::count_if(drawPanes.begin(), drawPanes.end(), [](const auto p)
                                       { return p->getSelected(); });
    std::cout << "total selected = " << total_selected << std::endl;

    if (total_selected > 1 && (event.GetKeyCode() == WXK_RIGHT || event.GetKeyCode() == WXK_LEFT))
    {
        // clear the selection
        for (auto &pane : drawPanes)
        {
            pane->setSelected(false);
        }
        return;
    }

    if (event.GetKeyCode() == WXK_RIGHT)
    {
        for (auto i = 0; i < drawPanes.size() - 1; ++i)
        {
            if (drawPanes[i]->getSelected() && !drawPanes[i + 1]->getSelected())
            {
                drawPanes[i]->setSelected(false);
                drawPanes[i + 1]->setSelected(true);
                break;
            }
        }

        // while (total_selected > 0)
        // {
        //     for (auto i = 0; i < drawPanes.size() - 1; ++i)
        //     {
        //         if (drawPanes[i]->getSelected() && !drawPanes[i + 1]->getSelected())
        //         {
        //             drawPanes[i]->setSelected(false);
        //             drawPanes[i + 1]->setSelected(true);
        //             break;
        //         }
        //     }
        //     --total_selected;
        // }
    }

    if (event.GetKeyCode() == WXK_LEFT)
    {
        for (int i = drawPanes.size() - 1; i > 0; --i)
        {
            if (drawPanes[i]->getSelected() && !drawPanes[i - 1]->getSelected())
            {
                drawPanes[i]->setSelected(false);
                drawPanes[i - 1]->setSelected(true);
                break;
            }
        }
    }
}

void MyFrame::OnRightClick(wxContextMenuEvent &event)
{
    std::cout << "FRAME RECEIVED RIGHT CLICK EVENT!!" << std::endl;
}

// ----------------------------------------
// how-to-use example

class MyApp : public wxApp
{
private:
    MyFrame *frame;

public:
    bool OnInit()
    {
        // make sure to call this first
        wxInitAllImageHandlers();

        frame = new MyFrame(wxT("Image Editor"), wxPoint(50, 50), wxSize(800, 600), wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER);
        frame->Show();
        return true;
    }
};

IMPLEMENT_APP(MyApp)
