#include "wx/wx.h"

#include <vector>
#include <set>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

std::vector<std::string> get_image_list(const std::string &path)
{
    int max_image_count{1};
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

class ImagePanel : public wxPanel
{
public:
    ImagePanel(wxFrame *parent, wxString file, wxBitmapType format);

    void paintEvent(wxPaintEvent &event);
    void paintNow();
    void render(wxDC &dc);

private:
    wxBitmap image;
};

ImagePanel::ImagePanel(wxFrame *parent, wxString file, wxBitmapType format)
    : wxPanel(parent)
{
    image.LoadFile(file, format);
}

void ImagePanel::paintEvent(wxPaintEvent &event)
{
    wxPaintDC dc(this);
    render(dc);
}

void ImagePanel::paintNow()
{
    wxClientDC dc(this);
    render(dc);
}

void ImagePanel::render(wxDC &dc)
{
    dc.DrawBitmap(image, 0, 0, false);
}

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);

private:
    std::vector<ImagePanel *> images;
    std::vector<std::string> imageList;
    wxGridSizer *sizer;
};

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    sizer = new wxGridSizer(3);
    std::string path = R"(C:/Users/aamir.ali/Pictures/demo-lib/)";
    auto image_list = get_image_list(path);

    for (const auto &img : image_list)
    {
        auto imgPane = new ImagePanel(this, img, wxBITMAP_TYPE_JPEG);
        sizer->Add(imgPane, 1, wxEXPAND);
        images.push_back(imgPane);
    }

    this->SetSizerAndFit(sizer);
}

class MyApp : public wxApp
{
public:
    bool OnInit();

private:
    MyFrame *frame;
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    // load the image handlers
    wxInitAllImageHandlers();

    frame = new MyFrame(wxT("Hello wxDC"), wxDefaultPosition, wxSize(600, 400));
    frame->Show();
    return true;
}
