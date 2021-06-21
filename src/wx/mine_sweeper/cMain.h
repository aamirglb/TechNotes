#pragma once

#include "wx/wx.h"

class cMain : public wxFrame
{
public:
    cMain();
    ~cMain();

public:
    //wxButton* m_btn1 = nullptr;
    //wxTextCtrl* m_txt1 = nullptr;
    //wxListBox* m_list1 = nullptr;
    int nFieldWidth = 10;
    int nFieldHeight = 10;
    wxButton** btn;
    int nPrevButton = -1;

    int* nField = nullptr;
    bool bFirstClick = true;
    void PrintSheetCode();

    void OnButtonClicked(wxCommandEvent& evt);

    // wxDECLARE_EVENT_TABLE();
};

