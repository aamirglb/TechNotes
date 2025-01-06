#include "translationhelper.h"
#include "wx/dir.h"
#include "wx/config.h"
#include "wx/filename.h"
#include "wx/log.h"

#include <iostream>
#include <fstream>

TranslationHelper::TranslationHelper(wxApp &app)
    : m_App{app}, m_Locale{nullptr}
{
    Load();
}

TranslationHelper::~TranslationHelper()
{
    Save();
    if (m_Locale)
    {
        wxDELETE(m_Locale);
    }
}

wxLocale *TranslationHelper::GetLocale()
{
    return m_Locale;
}

bool TranslationHelper::Load()
{
    wxConfig config(m_App.GetAppName());
    long language;

    if (!config.Read(wxT("wxTranslation_Language"), &language, wxLANGUAGE_UNKNOWN))
    {
        language = wxLANGUAGE_UNKNOWN;
    }

    if (language == wxLANGUAGE_UNKNOWN)
    {
        return false;
    }
    wxArrayString names;
    wxArrayLong identifiers;

    GetInstalledLanguages(names, identifiers);

    {
        std::ofstream out("output.txt", std::ios::out | std::ios::app);
        out << "count = " << identifiers.Count() << std::endl;
        out.close();
    }
    for (size_t i = 0; i < identifiers.Count(); ++i)
    {
        if (identifiers == language)
        {
            if (m_Locale)
                wxDELETE(m_Locale);
            m_Locale = new wxLocale;
            m_Locale->Init(identifiers[i]);
            m_Locale->AddCatalogLookupPathPrefix(wxPathOnly(m_App.argv[0]));
            m_Locale->AddCatalog(m_App.GetAppName());
        }
    }
    return false;
}

void TranslationHelper::Save(bool bReset)
{
    wxConfig config(m_App.GetAppName());
    long language = wxLANGUAGE_UNKNOWN;

    if (!bReset)
    {
        if (m_Locale)
        {
            language = m_Locale->GetLanguage();
        }
    }
    config.Write(wxT("wxTranslation_Language"), language);
    config.Flush();
}

void TranslationHelper::GetInstalledLanguages(wxArrayString &names, wxArrayLong &identifiers)
{
    names.Clear();
    identifiers.Clear();
    wxDir dir(wxPathOnly(m_App.argv[0]));
    wxString filename;
    const wxLanguageInfo *langinfo;
    wxString name = wxLocale::GetLanguageName(wxLANGUAGE_DEFAULT);
    if (!name.IsEmpty())
    {
        names.Add(_("Default"));
        identifiers.Add(wxLANGUAGE_DEFAULT);
    }

    for (bool cont = dir.GetFirst(&filename, wxT("*.*"), wxDIR_DIRS); cont; cont = dir.GetNext(&filename))
    {
        wxLogTrace(wxTRACE_Messages,
                   _("wxTranslationHelper: Directory found = \"%s\""),
                   filename.GetData());
        langinfo = wxLocale::FindLanguageInfo(filename);

        if (langinfo != nullptr)
        {
            if (wxFileExists(dir.GetName() + wxFileName::GetPathSeparator() + filename + wxFileName::GetPathSeparator() + m_App.GetAppName() + wxT(".mo")))
            {
                names.Add(langinfo->Description);
                identifiers.Add(langinfo->Language);
            }
        }
    }
}

bool TranslationHelper::AskUserForLanguage(wxArrayString &names, wxArrayLong &identifiers)
{
    wxCHECK_MSG(names.Count() == identifiers.Count(), false, _("Array of language names and identifiers should have the same size."));
    long index = wxGetSingleChoiceIndex(_("Select the language"), _("Language"), names);

    if (index != -1)
    {
        if (m_Locale)
        {
            wxDELETE(m_Locale);
        }
        m_Locale = new wxLocale;
        m_Locale->Init(identifiers[index]);
        m_Locale->AddCatalogLookupPathPrefix(wxPathOnly(m_App.argv[0]));
        wxLogTrace(wxTRACE_Messages,
                   _("wxTranslationHelper: Path Prefix = \"%s\""),
                   wxPathOnly(m_App.argv[0]).GetData());
        m_Locale->AddCatalog(m_App.GetAppName());
        wxLogTrace(wxTRACE_Messages,
                   _("wxTranslationHelper: Catalog Name = \"%s\""),
                   m_App.GetAppName().GetData());
        return true;
    }
    return false;
}