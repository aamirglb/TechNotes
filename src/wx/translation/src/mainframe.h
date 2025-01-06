#pragma once

#include "wx/wx.h"
#include "wx/listbox.h"

class MainFrame : public wxFrame
{
    void RefreshData();
    wxListBox *m_ListBox;
    void CreateControls();

public:
    MainFrame(wxWindow *parent = nullptr,
              wxWindowID id = wxID_ANY,
              const wxString title = _("wxTranslation Test"));
    bool Create(wxWindow *parent = nullptr,
                wxWindowID id = wxID_ANY,
                const wxString title = _("wxTranslation Test"),
                const wxPoint &pos = wxDefaultPosition,
                const wxSize &size = wxDefaultSize,
                long style = wxCAPTION | wxSYSTEM_MENU | wxCLOSE_BOX | wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxRESIZE_BORDER);

    void OnExit(wxCommandEvent &event);
    void OnToggleStatusBar(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);
    void OnToggleStatusBarUpdateUI(wxUpdateUIEvent &event);
    void OnSelectLanguage(wxCommandEvent &event);
    void OnAddValue(wxCommandEvent &event);

    void BindWxEvents();
};