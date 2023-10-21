#include "burning.h"
#include "widget.h"

enum
{
    ID_SLIDER = 1
};

Burning::Burning(const wxString &title) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(350, 200))
{
    m_CurWidth = 75;
    auto panel = new wxPanel(this, wxID_ANY);
    auto centerPanel = new wxPanel(panel, wxID_ANY);

    m_Slider = new wxSlider(centerPanel, ID_SLIDER, 75, 0, 750, wxPoint(-1, -1),
                            wxSize(150, -1), wxSL_LABELS);

    auto vbox = new wxBoxSizer(wxVERTICAL);
    auto hbox = new wxBoxSizer(wxHORIZONTAL);
    auto hbox2 = new wxBoxSizer(wxHORIZONTAL);
    auto hbox3 = new wxBoxSizer(wxHORIZONTAL);

    m_Widget = new Widget(panel, wxID_ANY);
    hbox->Add(m_Widget, 1, wxEXPAND);

    hbox2->Add(centerPanel, 1, wxEXPAND);
    hbox3->Add(m_Slider, 0, wxTOP | wxLEFT, 35);

    centerPanel->SetSizer(hbox3);
    vbox->Add(hbox2, 1, wxEXPAND);
    vbox->Add(hbox, 0, wxEXPAND);

    panel->SetSizer(vbox);
    m_Slider->SetFocus();

    // Bind(wxEVT_COMMAND_SLIDER_UPDATED, &Burning::OnScroll, this);
    Connect(ID_SLIDER, wxEVT_COMMAND_SLIDER_UPDATED,
            wxScrollEventHandler(Burning::OnScroll));
    Center();
}

void Burning::OnScroll(wxScrollEvent &WXUNUSED(event))
{
    m_CurWidth = m_Slider->GetValue();
    m_Widget->Refresh();
}

int Burning::GetCurWidth()
{
    return m_CurWidth;
}