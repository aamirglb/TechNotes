#include "wx/wx.h"

// TextControl class
class TextCtrl : public wxTextCtrl
{
public:
    TextCtrl(wxWindow* parent, wxWindowID id, const wxString& value = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxTextCtrlNameStr);
    void OnChar(wxKeyEvent& event);

private:
    DECLARE_EVENT_TABLE()
};

// Frame class : top-level window
class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title);

    // Event handlers
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnSize(wxSizeEvent& event);
    void OnButtonOK(wxCommandEvent& event);
    
private:
    // Declare events table
    DECLARE_EVENT_TABLE()
};

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};