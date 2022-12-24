#include "app.h"
#include "mondrian.xpm"
#include <iostream>

IMPLEMENT_APP(MyApp)
DECLARE_APP(MyApp)

BEGIN_DECLARE_EVENT_TYPES()
    DECLARE_EVENT_TYPE(wxEVT_COMMAND_FONT_SELECTION_CHANGED, 801)
END_DECLARE_EVENT_TYPES()


// Frame constructor
MyFrame::MyFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title)
{
    SetIcon(wxIcon(mondrian_xpm));

    wxMenu *fileMenu = new wxMenu;
    wxMenu *help = new wxMenu;
    help->Append(wxID_ABOUT, wxT("&About...\tF1"), wxT("Show about dialog"));
    fileMenu->Append(wxID_EXIT, wxT("E&xit\tAlt-X"), wxT("Quit this App"));

    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, wxT("&File"));
    menuBar->Append(help, wxT("&Help"));

    SetMenuBar(menuBar);

    CreateStatusBar(2);
    SetStatusText(wxT("Welcome to wxWidgets!"));
}


// About event handler
void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg;
    msg.Printf(wxT("Hello and welcome to %s"), wxVERSION_STRING);
    wxMessageBox(msg, wxT("About App"), wxOK | wxICON_INFORMATION, this);
    std::cout << "OnAbout clicked...\n";
    // OutputDebugStr("OnAbout clicked...");
}

void MyFrame::OnSize(wxSizeEvent& event)
{
}

void MyFrame::OnButtonOK(wxCommandEvent& event)
{
}

// Quit event handler
void MyFrame::OnQuit(wxCommandEvent& event)
{
    // Destroy frame
    Close();
}

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame(wxT("Hello wxWidget App"));
    frame->Bind(wxEVT_COMMAND_MENU_SELECTED, 
            &MyFrame::OnQuit,
            frame,
            wxID_EXIT
    );

    frame->Bind( wxEVT_COMMAND_MENU_SELECTED,
            &MyFrame::OnAbout,
            frame,
            wxID_ABOUT
    );

    // frame->Connect( wxID_EXIT, 
    //         wxEVT_COMMAND_MENU_SELECTED,
    //         wxCommandEventHandler(MyFrame::OnQuit) 
    // );

    // frame->Connect( wxID_ABOUT,
    //         wxEVT_COMMAND_MENU_SELECTED,
    //         wxCommandEventHandler(MyFrame::OnAbout)
    // );

    frame->Show(true);
    return true;
}
