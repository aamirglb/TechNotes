#include <wx/wx.h>

class MyDlg : public wxDialog
{
public:
    MyDlg() : wxDialog(NULL, wxID_ANY, "Test dialog", wxDefaultPosition, wxSize(400, 400))
    {
        wxPanel *panel = new wxPanel(this);
        m_twoPanelSizer = new wxBoxSizer(wxHORIZONTAL);

        m_panelA = new wxPanel(panel);
        m_panelA->SetBackgroundColour(*wxRED);
        m_twoPanelSizer->Add(m_panelA, 1, wxEXPAND | wxALL, 10);

        m_panelB = new wxPanel(panel);
        m_panelB->SetBackgroundColour(*wxBLUE);
        m_twoPanelSizer->Add(m_panelB, 1, wxEXPAND | wxALL, 10);

        wxButton *btn = new wxButton(panel, wxID_ANY, "Switch Red Panel");
        btn->Bind(wxEVT_BUTTON, &MyDlg::OnSwitchPanel, this);

        wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
        mainSizer->Add(m_twoPanelSizer, 1, wxEXPAND);
        mainSizer->Add(btn, 0, wxEXPAND | wxALL, 10);

        panel->SetSizer(mainSizer);
    }

private:
    wxBoxSizer *m_twoPanelSizer;
    wxPanel *m_panelA, *m_panelB;

    void OnSwitchPanel(wxCommandEvent &)
    {
        if (m_twoPanelSizer->GetItemCount() > 1)
            m_twoPanelSizer->Detach(m_panelA);
        else
            m_twoPanelSizer->Prepend(m_panelA, 1, wxEXPAND | wxALL, 10);
        m_twoPanelSizer->Layout();
    }
};

class MyApp : public wxApp
{
public:
    bool OnInit()
    {
        MyDlg dlg;

        dlg.ShowModal();
        return false;
    }
};
wxIMPLEMENT_APP(MyApp);