// g++ hello2.cpp `wx-config --cxxflags --libs std` -o hello2

#include <wx/wx.h>
#include <iostream>

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame {
public:
    MyFrame();
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnSize(wxSizeEvent& event);
    void OnButtonOK(wxCommandEvent& event);

// private:
//     DECLARE_EVENT_TABLE()
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
    wxFrame(nullptr, wxID_ANY, "Hello WxWidgets!!") 
{
    // SetIcon(wxIcon(modrian_xpm));

    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello\tCtrl-H",
        "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT, wxT("E&xit\tAlt-X"),
        wxT("Quit this program"));

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar(menuBar);

    CreateStatusBar(2);
    SetStatusText("Welcome to wxWidgets!");

    Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    // Bind(wxEVT_MENU, &MyFrame::onExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, [=](wxCommandEvent &){ Close(true); }, wxID_EXIT);
    Bind(wxEVT_BUTTON, &MyFrame::OnButtonOK, this, wxID_OK);
    Bind(wxEVT_SIZE, &MyFrame::OnSize, this);

    // Add a button
    wxButton* button = new wxButton(this, wxID_OK, wxT("OK"), wxPoint(50, 50));
}

// Event table for MyFrame

void MyFrame::OnExit(wxCommandEvent& event) {
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& event) {
    wxString msg;
    msg.Printf(wxT("Hello and welcome to %s"), wxVERSION_STRING);
    wxMessageBox(msg, "About Hello World", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnHello(wxCommandEvent& event) {
    wxLogMessage("Hello world from wxWidgets!");
}

void MyFrame::OnSize(wxSizeEvent& event) {
    std::cout << "Window Resized: " << event.GetSize().GetWidth() << " , " << event.GetSize().GetHeight() << '\n';
}

void MyFrame::OnButtonOK(wxCommandEvent& event) {
    std::cout << "Hello Button Pressed...\n";
}