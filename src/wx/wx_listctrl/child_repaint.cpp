#include <wx/wx.h>
#include <wx/dcbuffer.h>

#include <ctime>
#include <iostream>

class ChildControl : public wxWindow
{
public:
    ChildControl(wxWindow *parent) : wxWindow(parent, wxID_ANY)
    {
        SetBackgroundStyle(wxBG_STYLE_PAINT);
        Bind(wxEVT_PAINT, &ChildControl::OnPaint, this);
        colour_ = *wxRED;
    }

    wxColour colour_;

    void OnPaint(wxPaintEvent &event)
    {
        std::cout << "ChildControl::OnPaint" << std::endl;

        wxAutoBufferedPaintDC dc(this);
        dc.SetBrush(wxBrush(colour_));
        dc.DrawRectangle(GetClientRect());
    }

    void SetColour(const wxColour &colour)
    {
        colour_ = colour;
        Refresh();
    }
};

class ParentControl : public wxWindow
{
public:
    ChildControl *child;

    ParentControl(wxWindow *parent) : wxWindow(parent, wxID_ANY)
    {
        SetBackgroundStyle(wxBG_STYLE_PAINT);
        SetBackgroundColour(*wxRED);
        Bind(wxEVT_PAINT, &ParentControl::OnPaint, this);
        child = new ChildControl(this);
    }

    void OnPaint(wxPaintEvent &event)
    {
        std::cout << "ParentControl::OnPaint" << std::endl;
        wxAutoBufferedPaintDC dc(this);
        dc.Clear();
    }
};

class MyFrame : public wxFrame
{
public:
    wxTimer timer_;
    ParentControl *parent;

    MyFrame() : wxFrame(nullptr, wxID_ANY, "Test"), timer_(this)
    {
        auto *panel = new wxPanel(this);
        parent = new ParentControl(panel);
        timer_.Start(1000, wxTIMER_CONTINUOUS);

        Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
        Bind(wxEVT_TIMER, &MyFrame::OnTimer, this);
    }

private:
    void OnExit(wxCommandEvent &evt)
    {
        Close(true);
    }

    void OnTimer(wxTimerEvent &timer)
    {
        parent->child->SetColour(wxColour(
            std::rand() % 255,
            std::rand() % 255,
            std::rand() % 255));
    }
};

class MyApp : public wxApp
{
public:
    bool OnInit() override
    {
        std::srand(std::time(nullptr));
        MyFrame *frame = new MyFrame();
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);