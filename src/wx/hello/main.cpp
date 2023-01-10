#include <wx/wx.h>
#include <vector>

class Frame : public wxFrame
{
public:
    Frame(const wxString &title = "",
          const wxPoint &pos = wxDefaultPosition,
          const wxSize &size = wxDefaultSize);

private:
    std::vector<wxButton *> m_Buttons;
};

Frame::Frame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
    for (int i = 0; i < 3; ++i)
    {
        auto button = new wxButton(this,
                                   wxID_ANY,
                                   wxString::Format("Button - %d", i),
                                   wxDefaultPosition,
                                   wxSize(120, 24));

        m_Buttons.push_back(button);
        mainSizer->Add(button, 0, wxEXPAND | wxALL, 5);
    }

    SetSizer(mainSizer);
    Layout();
}

class App : public wxApp
{
public:
    virtual bool OnInit() override;

private:
    Frame *m_Frame;
};

bool App::OnInit()
{
    m_Frame = new Frame("Test");
    m_Frame->CreateStatusBar(2, wxST_SIZEGRIP);
    int widths[3] = {100, 200, -1};
    m_Frame->SetStatusWidths(2, widths);
    m_Frame->SetStatusText(_("Ready"), 0);
    m_Frame->SetStatusText(_("Click To Start"), 1);
    m_Frame->Show();

    return true;
}

wxIMPLEMENT_APP(App);