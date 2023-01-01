#include "wx/wx.h"
#include "wx/listctrl.h"

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
};

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame("Hello wxWidgets", wxDefaultPosition, wxDefaultSize);
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    wxListView *list = new wxListView(this, wxID_ANY, wxDefaultPosition, wxSize(300, 200));
    list->InsertColumn(0, "Name");
    list->InsertItem(0, "Item");

    wxButton *ok_button = new wxButton(this, wxID_ANY, "OK");
    wxButton *cancel_button = new wxButton(this, wxID_ANY, "Cancel");

    wxBoxSizer *s1 = new wxBoxSizer(wxVERTICAL);
    s1->Add(list, 1, wxEXPAND | wxALL, 5);

    wxBoxSizer *s2 = new wxBoxSizer(wxHORIZONTAL);
    s2->Add(ok_button, 0, wxRIGHT, 5);
    s2->Add(cancel_button, 0);

    s1->Add(s2, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM, 5);
    this->SetSizerAndFit(s1);
}

