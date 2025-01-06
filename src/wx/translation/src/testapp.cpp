#include "testapp.h"
#include "mainframe.h"

IMPLEMENT_APP(TestApp)

bool TestApp::OnInit()
{
    m_TranslationHelper = new TranslationHelper(*this);
    RecreateGUI();
    return true;
}

int TestApp::OnExit()
{
    if (m_TranslationHelper)
    {
        wxDELETE(m_TranslationHelper);
    }
    return 0;
}

void TestApp::RecreateGUI()
{
    wxWindow *topwindow = GetTopWindow();
    if (topwindow)
    {
        SetTopWindow(nullptr);
        topwindow->Destroy();
    }
    MainFrame *frame = new MainFrame;
    SetTopWindow(frame);
    frame->Center();
    frame->Show();
}

bool TestApp::SelectLanguage()
{
    wxArrayString names;
    wxArrayLong identifiers;
    m_TranslationHelper->GetInstalledLanguages(names, identifiers);
    return m_TranslationHelper->AskUserForLanguage(names, identifiers);
}

wxArrayString &TestApp::GetDocument()
{
    return m_Document;
}