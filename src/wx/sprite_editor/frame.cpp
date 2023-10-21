#include "frame.h"
#include "utils.h"

Frame::Frame(const wxString &title, const wxPoint &pos, wxSize &size, long style)
    : wxMDIParentFrame(nullptr, wxID_ANY, title, pos, size, style)
{
    m_MenuBar = new wxMenuBar();
    this->SetMenuBar(m_MenuBar);

    wxMenu *fileMenu = new wxMenu();
    fileMenu->Append(10'001, "New\tCtrl-N");
    fileMenu->Append(10'002, "Open\tCtrl-O");
    fileMenu->Append(10'003, "Save\tCtrl-S");
    fileMenu->Append(10'004, "Exit\tAlt-X");
    m_MenuBar->Append(fileMenu, "File");

    this->Bind(wxEVT_MENU, &Frame::OnMenuNew, this, 10'001);
    this->Bind(wxEVT_MENU, &Frame::OnMenuOpen, this, 10'002);
    this->Bind(wxEVT_MENU, &Frame::OnMenuSave, this, 10'003);
    this->Bind(wxEVT_MENU, &Frame::OnMenuExit, this, 10'004);

    m_ToolBar = this->CreateToolBar(wxTB_HORIZONTAL, wxID_ANY);

    for (int i = 0; i < 16; ++i)
    {
        wxButton *button = new wxButton(m_ToolBar, 10'100 + i, "", wxDefaultPosition, wxSize(40, 24), 0);
        button->SetBackgroundColour(Utils::palette[i]);
        button->Bind(wxEVT_BUTTON, &Frame::OnSelectColour, this);
        m_ToolBar->AddControl(button);
    }

    wxButton *alphaButton = new wxButton(m_ToolBar, 10'100 + 16, "ALPHA", wxDefaultPosition, wxDefaultSize, 0);
    alphaButton->Bind(wxEVT_BUTTON, &Frame::OnSelectColour, this);
    m_ToolBar->AddControl(alphaButton);
    m_ToolBar->Realize();
}

Frame::~Frame()
{
}

void Frame::OnMenuNew(wxCommandEvent &event)
{
    auto *e = new Editor(this, "Test");
    e->New(32, 32);
    e->Show();
    event.Skip();
}

void Frame::OnMenuOpen(wxCommandEvent &event)
{
    wxFileDialog dlg(this,
                     "Open olcSprite File",
                     "",
                     "",
                     ".spr Files (*.spr)|*.spr",
                     wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (dlg.ShowModal() == wxID_OK)
    {
        Editor *editor = new Editor(this, dlg.GetPath());
        editor->Open(dlg.GetPath());
        editor->Show();
    }
    event.Skip();
}

void Frame::OnMenuSave(wxCommandEvent &event)
{
    if (GetActiveChild() != nullptr)
    {
        wxFileDialog dlg(this,
                         "Save olcSprite File",
                         "",
                         "",
                         ".spr Files (*.spr)|*.spr",
                         wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

        if (dlg.ShowModal() == wxID_OK)
        {
            static_cast<Editor *>(GetActiveChild())->Save(dlg.GetPath());
        }
    }
}

void Frame::OnMenuExit(wxCommandEvent &event)
{
    Close();
    event.Skip();
}

void Frame::OnSelectColour(wxCommandEvent &event)
{
    int colour = event.GetId() - 10'100;
    if (GetActiveChild() != nullptr)
    {
        static_cast<Editor *>(GetActiveChild())->SetColour(colour);
    }
}
