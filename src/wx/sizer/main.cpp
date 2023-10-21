#include "wx/wx.h"
#include <vector>

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
    void OnButtonClick(wxCommandEvent &event);
    void OnItemSelectionChanged(wxCommandEvent &event);

private:
    wxComboBox *comboBox;
    std::vector<wxButton *> buttons;
    std::vector<bool> visibility;
    wxBoxSizer *leftSizer;
    wxBoxSizer *rightSizer;
    wxBoxSizer *mainSizer;
};

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame("Hello wxWidgets", wxDefaultPosition, wxDefaultSize);
    frame->Show(true);
    return true;
}

void MyFrame::OnButtonClick(wxCommandEvent &event)
{
    wxLogMessage("Button %d clicked.", event.GetId());
    std::cout << "Button clicked..." << event.GetId() << std::endl;
}

void MyFrame::OnItemSelectionChanged(wxCommandEvent &event)
{
    // wxLogMessage("Selected Value: %s", comboBox->GetValue());
    int index{};
    comboBox->GetValue().ToInt(&index);
    index -= 10'001;
    visibility[index] = !visibility[index];
    buttons[index]->Show(visibility[index]);

    bool success{true};
    if (!visibility[index])
    {
        auto idx = leftSizer->GetChildren().IndexOf(leftSizer->GetItem(buttons[index]));
        success &= leftSizer->Hide(idx);
        success &= leftSizer->Detach(buttons[index]);
    }
    else
    {
        leftSizer->Add(buttons[index], 1, wxEXPAND | wxALL, 4);
        // auto idx = leftSizer->GetChildren().IndexOf(leftSizer->GetItem(buttons[index]));
        // success &= leftSizer->Show(idx);
        // success &= leftSizer-> Detach(leftSizer);
    }
    Layout();
    SetSizerAndFit(mainSizer);
}

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    leftSizer = new wxBoxSizer(wxVERTICAL);

    wxArrayString choices;
    for (int i = 0; i < 5; ++i)
    {
        auto button = new wxButton(this, 10'001 + i, wxString::Format("Butto-%d", i + 1), wxDefaultPosition, wxSize(80, 24));
        button->Bind(wxEVT_BUTTON, &MyFrame::OnButtonClick, this);
        leftSizer->Add(button, 1, wxEXPAND | wxALL, 4);
        choices.Add(wxString::Format("%d", 10'001 + i));
        buttons.push_back(button);
        visibility.push_back(true);
    }

    comboBox = new wxComboBox(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, choices);
    comboBox->Bind(wxEVT_COMBOBOX, &MyFrame::OnItemSelectionChanged, this);

    rightSizer = new wxBoxSizer(wxVERTICAL);
    rightSizer->Add(comboBox, 1, wxEXPAND | wxALL, 4);

    mainSizer = new wxBoxSizer(wxHORIZONTAL);
    mainSizer->Add(leftSizer);
    mainSizer->Add(rightSizer);
    this->SetSizerAndFit(mainSizer);
    // wxPanel *panel_top = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 100));
    // panel_top->SetBackgroundColour(wxColor(100, 100, 200));

    // wxPanel *panel_bottom = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 100));
    // panel_bottom->SetBackgroundColour(wxColor(100, 200, 100));

    // wxPanel *panel_bottom_right = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 100));
    // panel_bottom_right->SetBackgroundColour(wxColor(200, 200, 100));

    // wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    // sizer->Add(panel_top, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);

    // wxSizer *sizer_bottom = new wxBoxSizer(wxHORIZONTAL);
    // sizer_bottom->Add(panel_bottom, 1, wxEXPAND | wxRIGHT, 10);
    // sizer_bottom->Add(panel_bottom_right, 0, wxEXPAND, 0);

    // sizer->Add(sizer_bottom, 1, wxEXPAND | wxALL, 10);

    // this->SetSizerAndFit(sizer);
}
