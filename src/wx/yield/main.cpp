#include "wx/wx.h"
#include <chrono>

class MyApp : public wxApp
{
public:
    virtual bool OnInit() override;
};

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
    virtual ~MyFrame() {}

private:
    wxButton *button;
    wxButton *otherButton;

    wxStaticText *label;
    wxGauge *progressBar;

    void OnButtonClick(wxCommandEvent &event);
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame("wxYield Demo", wxPoint(50, 50), wxDefaultSize);
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    wxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    wxSizer *centeringSizer = new wxBoxSizer(wxHORIZONTAL);

    wxPanel *panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, this->FromDIP(wxSize(320, 240)));
    wxSizer *panelSizer = new wxBoxSizer(wxVERTICAL);

    label = new wxStaticText(panel, wxID_ANY, "Click Start", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL);
    progressBar = new wxGauge(panel, wxID_ANY, 1000);

    button = new wxButton(panel, wxID_ANY, "START");
    button->Bind(wxEVT_BUTTON, &MyFrame::OnButtonClick, this);
    otherButton = new wxButton(panel, wxID_ANY, "Other Button");

    panelSizer->Add(label, 1, wxEXPAND | wxALL, this->FromDIP(20));
    panelSizer->Add(progressBar, 1, wxEXPAND | wxALL, this->FromDIP(20));
    panelSizer->Add(button, 0, wxALIGN_CENTER | wxALL, this->FromDIP(5));
    panelSizer->Add(otherButton, 0, wxALIGN_CENTER | wxBOTTOM, this->FromDIP(20));

    panel->SetSizer(panelSizer);
    centeringSizer->Add(panel, 0, wxALIGN_CENTER);
    sizer->Add(centeringSizer, 1, wxALIGN_CENTER);

    this->SetSizerAndFit(sizer);
}

void MyFrame::OnButtonClick(wxCommandEvent &event)
{
    std::vector<int> v(50'000, 5);
    v.back() = 3;

    int n = v.size();

    this->label->SetLabelText(wxString::Format("Sorting the array of %d elements...", n));
    this->Layout();

    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < n - 1; ++i)
    {
        this->progressBar->SetValue(i * this->progressBar->GetRange() / (n - 2));
        // wxYield();
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (v[j] > v[j + 1])
            {
                std::swap(v[j], v[j + 1]);
            }
        }
    }
    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;

    this->label->SetLabelText(wxString::Format("The first number is: %d\nProcessing Time: %.2f",
                                               v.front(),
                                               std::chrono::duration<double, std::milli>(diff).count()));
    this->Layout();
}