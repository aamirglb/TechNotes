#include <wx/wx.h>
#include <iostream>

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
};

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame("Hello World - SO", wxPoint(50, 50), wxSize(450, 340));
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
}

wxIMPLEMENT_APP(MyApp);

int main()
{
    std::cout << "Hello world, why isn't there a window showing?\n"
              << std::endl;
}