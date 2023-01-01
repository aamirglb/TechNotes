#include "wx/wx.h"

// font selector event class
class wxFontSelectorCtrlEvent : public wxNotifyEvent
{
public:
    wxFontSelectorCtrlEvent(wxEventType commandType = wxEVT_NULL, int id = 0)
        : wxNotifyEvent(commandType, id)
    {}

    wxFontSelectorCtrlEvent(const wxFontSelectorCtrlEvent& event)
        : wxNotifyEvent(event)
    {}

    virtual wxEvent* Clone() const 
    {
        return new wxFontSelectorCtrlEvent(*this);
    }

    DECLARE_DYNAMIC_CLASS(wxFontSelectorCtrlEvent);
};

using wxFontSelectorCtrlEventFunction = void (wxEvtHandler::*)(wxFontSelectorCtrlEvent&);

BEGIN_DECLARE_EVENT_TYPES()
    DECLARE_EVENT_TYPE(wxEVT_COMMAND_FONT_SELECTION_CHANGED, 801)
END_DECLARE_EVENT_TYPES()

#define EVT_FONT_SELECTION_CHANGED(id, fn) DECLARE_EVENT_TABLE_ENTRY(
    wxEVT_COMMAND_FONT_SELECTION_CHANGED, id, -1, (wxObjectEventFunction)
    (wxEventFunction) (wxFontSelectorCtrlEventFunction) & fn,
    (wxObject *) nullptr),
    
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
    // DECLARE_EVENT_TABLE()
};

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};