// g++ hello2.cpp `wx-config --cxxflags --libs std` -o hello2

#include <wx/wx.h>

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame {
public:
    MyFrame();

private:
    void onHello(wxCommandEvent& event);
    void onExit(wxCommandEvent& event);
    void onAbout(wxCommandEvent& event);
};

enum {
    ID_Hello = 1
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    MyFrame *frame = new MyFrame();
    frame->Show(true);
    return true;
}

MyFrame::MyFrame() :
    wxFrame(NULL, wxID_ANY, "Hello Wx") 
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
        "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar(menuBar);

    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");

    Bind(wxEVT_MENU, &MyFrame::onHello, this, ID_Hello);
    Bind(wxEVT_MENU, &MyFrame::onAbout, this, wxID_ABOUT);
    // Bind(wxEVT_MENU, &MyFrame::onExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, [=](wxCommandEvent &){ Close(true); }, wxID_EXIT);
}

void MyFrame::onExit(wxCommandEvent& event) {
    Close(true);
}

void MyFrame::onAbout(wxCommandEvent& event) {
    wxMessageBox("This is a wxWidgets Hello World example",
        "About Hello World", wxOK | wxICON_INFORMATION);
}

void MyFrame::onHello(wxCommandEvent& event) {
    wxLogMessage("Hello world from wxWidgets!");
}

