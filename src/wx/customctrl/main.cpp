#include "wx/wx.h"
#include "drawingcanvas.h"

#include <random>

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);

private:
    void OnAddButtonClick(wxCommandEvent &event);
    void OnRemoveButtonClick(wxCommandEvent &event);

    void OnRectAdded(wxCommandEvent &event);
    void OnRectRemoved(wxCommandEvent &event);
    // void OnTimer(wxTimerEvent &event);
    wxPanel *createButtonPanel(wxWindow *parent);

    DrawingCanvas *canvas;
    int rectCount{};
    std::mt19937 randomGen;
    // wxTimer *timer;
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame("Custom Controls", wxPoint(50, 50), wxSize(640, 480));
    frame->Show();
    return true;
}

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    wxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    auto buttonPanel = createButtonPanel(this);

    canvas = new DrawingCanvas(this, wxID_ANY, wxDefaultPosition, this->FromDIP(wxSize(640, 480)));
    canvas->Bind(CANVAS_RECT_ADDED, &MyFrame::OnRectAdded, this);
    canvas->Bind(CANVAS_RECT_REMOVED, &MyFrame::OnRectRemoved, this);

    rectCount = canvas->getObjectCount();

    sizer->Add(canvas, 1, wxEXPAND | wxALL, 0);
    sizer->Add(buttonPanel, 0, wxEXPAND | wxALL, 0);

    this->SetSizerAndFit(sizer);

    CreateStatusBar(1);
    SetStatusText("Ready", 0);

    // timer = new wxTimer(this, 5'003);
    // timer->Bind(wxEVT_TIMER, &MyFrame::OnTimer, this, 5'003);
    // timer->Start(1000);
}

// void MyFrame::OnTimer(wxTimerEvent &event)
// {
//     std::cout << "%%%%%%%%%% timer click %%%%%%%%%%%" << std::endl;
// }
void MyFrame::OnAddButtonClick(wxCommandEvent &event)
{
    std::uniform_int_distribution<int> sizeDistrib(this->FromDIP(50), this->FromDIP(100));
    std::uniform_int_distribution<int> xDistrib(0, canvas->GetSize().GetWidth());
    std::uniform_int_distribution<int> yDistrib(0, canvas->GetSize().GetHeight());
    std::uniform_int_distribution<int> angleDistrib(0.0, M_PI * 2.0);
    std::uniform_int_distribution<int> colorDistrib(0, 0xFFFFFF);

    ++rectCount;
    canvas->addRect(sizeDistrib(randomGen),
                    sizeDistrib(randomGen),
                    xDistrib(randomGen),
                    yDistrib(randomGen),
                    angleDistrib(randomGen),
                    wxColour(colorDistrib(randomGen)),
                    "Rect #" + std::to_string(rectCount));
}

void MyFrame::OnRemoveButtonClick(wxCommandEvent &event)
{
    canvas->removeTopRect();
}

void MyFrame::OnRectAdded(wxCommandEvent &event)
{
    SetStatusText("Rect named " + event.GetString() + " added!", 0);
}

void MyFrame::OnRectRemoved(wxCommandEvent &event)
{
    SetStatusText("Rect named " + event.GetString() + " REMOVED!!", 0);
}

wxPanel *MyFrame::createButtonPanel(wxWindow *parent)
{
    wxPanel *panel = new wxPanel(parent);
    wxButton *addRectButton = new wxButton(panel, wxID_ANY, "Add Rect");
    wxButton *removeButton = new wxButton(panel, wxID_ANY, "Remove Top");

    wxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(addRectButton, 0, wxEXPAND | wxALL, 3);
    sizer->Add(removeButton, 0, wxEXPAND | wxALL, 3);

    panel->SetSizer(sizer);
    addRectButton->Bind(wxEVT_BUTTON, &MyFrame::OnAddButtonClick, this);
    removeButton->Bind(wxEVT_BUTTON, &MyFrame::OnRemoveButtonClick, this);

    return panel;
}
