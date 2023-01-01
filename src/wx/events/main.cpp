#include "wx/wx.h"
#include <iostream>

class MyApp : public wxApp
{
public:
    bool OnInit() override;
};

wxIMPLEMENT_APP(MyApp);

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);

private:
    void OnClick(wxCommandEvent &);
    wxDECLARE_EVENT_TABLE();
};

enum ButtonID
{
    BUTTON = wxID_LAST + 1,
    BUTTON2,
};

// clang-format off
wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_BUTTON(wxID_ANY, MyFrame::OnClick)
wxEND_EVENT_TABLE()

; // clang-format on

class MyPanel : public wxPanel
{
public:
    MyPanel(wxWindow *parent);

private:
    void OnClick(wxCommandEvent &);
    wxDECLARE_EVENT_TABLE();
};

MyPanel::MyPanel(wxWindow *parent)
    : wxPanel(parent)
{
    this->SetBackgroundColour(wxColor(200, 100, 100));
}

void MyPanel::OnClick(wxCommandEvent &e)
{
    std::cout << "Panel clicked, id = " << e.GetId() << std::endl;
    e.Skip();
}
// clang-format off
wxBEGIN_EVENT_TABLE(MyPanel, wxPanel)
EVT_BUTTON(wxID_ANY, MyPanel::OnClick)
wxEND_EVENT_TABLE()

; // clang-format on

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame("events", wxDefaultPosition, wxDefaultSize);
    frame->Show();
    return true;
}

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    auto panel = new MyPanel(this);

    auto button = new wxButton(panel, BUTTON, "click");
    auto panelSizer = new wxBoxSizer(wxHORIZONTAL);
    panelSizer->Add(button, 0, wxCENTER | wxALL, 100);
    panel->SetSizerAndFit(panelSizer);

    auto button2 = new wxButton(this, BUTTON2, "click-2");

    auto sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(panel, 0, wxEXPAND);
    sizer->Add(button2, 0, wxCENTER | wxALL, 100);

    SetSizerAndFit(sizer);
}

void MyFrame::OnClick(wxCommandEvent &e)
{
    std::cout << "Button-ID: " << e.GetId() << std::endl;
}