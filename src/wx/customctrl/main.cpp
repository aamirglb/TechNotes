#include "wx/wx.h"
#include "drawingcanvas.h"

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
    DrawingCanvas *canvas;
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
    canvas = new DrawingCanvas(this, wxID_ANY, wxDefaultPosition, this->FromDIP(wxSize(640, 480)));

    sizer->Add(canvas, 0, wxEXPAND | wxALL, 0);
    this->SetSizerAndFit(sizer);
}
