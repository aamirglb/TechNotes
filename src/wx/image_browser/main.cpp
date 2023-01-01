#include "wx/wx.h"

#include "frame.h"

class MyApp : public wxApp
{
public:
    bool OnInit() override;

private:
    Frame *m_Frame;
};

bool MyApp::OnInit()
{
    // load all the image plugins
    wxInitAllImageHandlers();

    m_Frame = new Frame(wxT("Image Browser"), wxPoint(50, 50), wxSize(1000, 800) /*, wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER*/);
    m_Frame->Show();
    return true;
}

IMPLEMENT_APP(MyApp)