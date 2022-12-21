#include "app.h"
#include "mondrian.xpm"

IMPLEMENT_APP(MyApp)
DECLARE_APP(MyApp)

// Event table for MyFrame class
BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU   (wxID_ABOUT, MyFrame::OnAbout)
    EVT_MENU   (wxID_EXIT,  MyFrame::OnQuit)
    EVT_SIZE   (            MyFrame::OnSize)
    EVT_BUTTON (wxID_OK,    MyFrame::OnButtonOK)
END_EVENT_TABLE()

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

    // add a button
    wxButton* button = new wxButton(this, wxID_OK, wxT("OK"), wxPoint(10, 10), wxSize(50, 22));
    wxButton* button2 = new wxButton(this, wxID_ANY, wxT("OK-2"), wxPoint(10, 35), wxSize(50, 22));
    TextCtrl* textCtrl = new TextCtrl(this, 10001, "", wxPoint(10, 55), wxSize(100, 22));
    wxTextCtrl* textCtrl2 = new wxTextCtrl(this, 10'002, "", wxPoint(10, 75), wxSize(100, 22));

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
    frame->Show(true);
    return true;
}


BEGIN_EVENT_TABLE(TextCtrl, wxTextCtrl)
    EVT_KEY_DOWN (TextCtrl::OnChar )
END_EVENT_TABLE()

TextCtrl::TextCtrl(wxWindow* parent, wxWindowID id, const wxString& value, const wxPoint& pos, const wxSize& size, long style, const wxValidator& validator, const wxString& name)
    : wxTextCtrl(parent, id, value, pos, size, style, validator, name)
{

}

void TextCtrl::OnChar(wxKeyEvent& event)
{
    if (wxIsalpha(event.GetKeyCode())) {
        event.Skip();
    }
    else if (event.GetKeyCode() == 8 || event.GetKeyCode() == 32) {
        event.Skip();
    }
    else {
        wxBell();
    }
}
