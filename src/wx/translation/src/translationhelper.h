#pragma

#include "wx/wx.h"
#include "wx/intl.h"

class TranslationHelper
{
    wxApp &m_App;
    wxLocale *m_Locale;

public:
    TranslationHelper(wxApp &app);
    ~TranslationHelper();

    wxLocale *GetLocale();
    void GetInstalledLanguages(wxArrayString &names, wxArrayLong &identifiers);
    bool AskUserForLanguage(wxArrayString &names, wxArrayLong &identifiers);
    bool Load();
    void Save(bool bReset = false);
};