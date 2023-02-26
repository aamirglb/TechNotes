#include <wx/wx.h>
#include <vector>

class Frame : public wxFrame
{
public:
    Frame(const wxString &title = "",
          const wxPoint &pos = wxDefaultPosition,
          const wxSize &size = wxDefaultSize);

private:
    void OnKeyDown(wxKeyEvent &event);
    std::vector<wxButton *> m_Buttons;
    wxFlexGridSizer *mainSizer;
};

Frame::Frame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    Bind(wxEVT_KEY_DOWN, &Frame::OnKeyDown, this);
    mainSizer = new wxFlexGridSizer(1);
    // wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
    for (int i = 0; i < 2; ++i)
    {
        auto button = new wxButton(this,
                                   wxID_ANY,
                                   wxString::Format("Button - %d", i),
                                   wxDefaultPosition,
                                   wxSize(120 + (i * 20), 24));

        m_Buttons.push_back(button);
        mainSizer->Add(button, 1, wxALL, 5);
    }

    SetSizer(mainSizer);
    Layout();
}

void Frame::OnKeyDown(wxKeyEvent &event)
{
    auto keyCode = event.GetKeyCode();
    if (keyCode == WXK_UP)
    {
        // this->GetSizer()->Clear(true);
        // this->SetSizer(nullptr, true);
        // mainSizer = new wxFlexGridSizer(1);

        auto &[width, height] = m_Buttons[0]->GetSize();
        std::cout << "(" << width << ", " << height << ")" << std::endl;
        width *= 1.1;
        height *= 1.1;
        m_Buttons[0]->SetMinSize(wxSize(width, height));
        std::cout << "Button size set to (" << width << ", " << height
                  << ")" << std::endl;

        // mainSizer->Add(m_Buttons[0], 1, wxALL, 5);
        // mainSizer->Add(m_Buttons[1], 1, wxALL, 5);
        // this->SetSizer(mainSizer);
        // mainSizer->Layout();
        Layout();
    }
    event.Skip();
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
    // wxFlexGridSizer *sizer = new wxFlexGridSizer(1);

    m_Frame = new Frame("Resize Test");
    // m_Frame->CreateStatusBar(2, wxST_SIZEGRIP);
    // int widths[3] = {100, 200, -1};
    // m_Frame->SetStatusWidths(2, widths);
    // m_Frame->SetStatusText(_("Ready"), 0);
    // m_Frame->SetStatusText(_("Click To Start"), 1);
    m_Frame->Show();

    return true;
}

wxIMPLEMENT_APP(App);