#include "main.h"
#include "burning.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    auto burning = new Burning(wxT("The Burning Widget"));
    burning->Show(true);
    return true;
}
