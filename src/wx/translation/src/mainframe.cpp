#include "mainframe.h"
#include "testapp.h"
#include "wx/textdlg.h"

wxDECLARE_APP(TestApp);

enum wxTranslationTestMainFrameIDs
{
    ID_TOGGLE_STATUSBAR = 10001,
    ID_LISTBOX,
    ID_SELECT_LANGUAGE,
    ID_ADD_VALUE,
};

MainFrame::MainFrame(wxWindow *parent, wxWindowID id, const wxString title)
{
    Create(parent, id, title);
}

bool MainFrame::Create(wxWindow *parent, wxWindowID id, const wxString title, const wxPoint &pos, const wxSize &size, long style)
{
    bool res = wxFrame::Create(parent, id, title, pos, size, style);
    if (res)
    {
        CreateControls();
    }
    return res;
}

void MainFrame::CreateControls()
{
    wxMenuBar *menuBar = new wxMenuBar;
    SetMenuBar(menuBar);

    wxMenu *fileMenu = new wxMenu;
    fileMenu->Append(wxID_EXIT, _("Exit\tAlt+F4"));

    wxMenu *viewMenu = new wxMenu;
    viewMenu->Append(ID_SELECT_LANGUAGE, _("Languages"));
    viewMenu->AppendCheckItem(ID_TOGGLE_STATUSBAR, _("Status Bar"));

    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(wxID_ABOUT, _("About..."));

    wxMenu *documentMenu = new wxMenu;
    documentMenu->Append(ID_ADD_VALUE, _("Add new item to document"));

    menuBar->Append(fileMenu, _("File"));
    menuBar->Append(viewMenu, _("View"));
    menuBar->Append(helpMenu, _("Help"));
    menuBar->Append(documentMenu, _("Document"));

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(sizer);

    m_ListBox = new wxListBox(this, wxID_ANY);
    sizer->Add(m_ListBox, 1, wxEXPAND);

    CreateStatusBar(2);
    BindWxEvents();
}

void MainFrame::OnExit(wxCommandEvent &event)
{
    Close();
}

void MainFrame::OnToggleStatusBar(wxCommandEvent &event)
{
    wxStatusBar *statusBar = GetStatusBar();
    if (statusBar)
    {
        SetStatusBar(nullptr);
        statusBar->Destroy();
    }
    else
    {
        CreateStatusBar(2);
    }
}

void MainFrame::OnAbout(wxCommandEvent &event)
{
    wxMessageBox(_("wxTranslation Test"));
}

void MainFrame::OnToggleStatusBarUpdateUI(wxUpdateUIEvent &event)
{
    event.Check(GetStatusBar() != nullptr);
}

void MainFrame::OnSelectLanguage(wxCommandEvent &event)
{
    if (wxGetApp().SelectLanguage())
    {
        wxGetApp().RecreateGUI();
    }
}

void MainFrame::OnAddValue(wxCommandEvent &event)
{
    wxString newValue = wxGetTextFromUser(
        _("Add new item to document"),
        _("Change some data"));

    if (!newValue.IsEmpty())
    {
        wxGetApp().GetDocument().Add(newValue);
        RefreshData();
    }
}

void MainFrame::RefreshData()
{
    m_ListBox->Freeze();
    m_ListBox->Clear();

    for (size_t i = 0; i < wxGetApp().GetDocument().Count(); ++i)
    {
        m_ListBox->Append(wxGetApp().GetDocument()[i]);
    }
    m_ListBox->Thaw();
}

void MainFrame::BindWxEvents()
{
    Bind(wxEVT_MENU, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &MainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MainFrame::OnToggleStatusBar, this, ID_TOGGLE_STATUSBAR);
    Bind(wxEVT_MENU, &MainFrame::OnSelectLanguage, this, ID_SELECT_LANGUAGE);
    Bind(wxEVT_MENU, &MainFrame::OnAddValue, this, ID_ADD_VALUE);
    Bind(wxEVT_UPDATE_UI, &MainFrame::OnToggleStatusBarUpdateUI, this, ID_TOGGLE_STATUSBAR);
}