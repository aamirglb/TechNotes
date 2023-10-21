#pragma once

#include "editor.h"
#include <wx/wx.h>

class Frame : public wxMDIParentFrame
{
public:
    Frame(const wxString &title, const wxPoint &pos, wxSize &size, long style = wxDEFAULT_FRAME_STYLE);
    ~Frame();

private:
    wxToolBar *m_ToolBar = nullptr;
    wxMenuBar *m_MenuBar = nullptr;

    void OnMenuNew(wxCommandEvent &event);
    void OnMenuOpen(wxCommandEvent &event);
    void OnMenuSave(wxCommandEvent &event);
    void OnMenuExit(wxCommandEvent &event);

    void OnSelectColour(wxCommandEvent &event);
};