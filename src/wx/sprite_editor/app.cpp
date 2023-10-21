#include "app.h"
#include "utils.h"

wxColor Utils::palette[16] = {
    wxColour(0, 0, 0),
    wxColour(0, 0, 128),
    wxColour(0, 128, 0),
    wxColour(0, 128, 128),
    wxColour(128, 0, 0),
    wxColour(128, 0, 128),
    wxColour(128, 128, 0),
    wxColour(192, 192, 192),
    wxColour(128, 128, 128),
    wxColour(0, 0, 255),
    wxColour(0, 255, 0),
    wxColour(0, 255, 255),
    wxColour(255, 0, 0),
    wxColour(255, 0, 255),
    wxColour(255, 255, 0),
    wxColour(255, 255, 255)};

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
    m_Frame = new Frame("Sprite Editor", wxPoint(50, 50), wxSize(1240, 768));
    m_Frame->Show();
    return true;
}
