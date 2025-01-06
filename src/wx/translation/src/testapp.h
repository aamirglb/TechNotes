#pragma once

#include "translationhelper.h"
#include "wx/wx.h"

class TestApp : public wxApp
{
    TranslationHelper *m_TranslationHelper;
    wxArrayString m_Document;

public:
    virtual bool OnInit();
    virtual int OnExit();
    void RecreateGUI();
    bool SelectLanguage();
    wxArrayString &GetDocument();
};
