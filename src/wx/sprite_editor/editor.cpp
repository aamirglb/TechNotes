#include "editor.h"
#include "utils.h"

Editor::Editor(wxMDIParentFrame *parent, const wxString &name)
    : wxMDIChildFrame(parent, wxID_ANY, name)
{
    m_Canvas = new Canvas(this);

    m_StatusBar = this->CreateStatusBar(3, wxSTB_DEFAULT_STYLE, wxID_ANY);
    wxRect rect;
    auto result = m_StatusBar->GetFieldRect(1, rect);
    m_ZoomSlider = new wxSlider(m_StatusBar, 20'001, 8, 1, 32);
    m_CurrentColour = new wxButton(this, 20'002, "", wxPoint(10, 10), wxSize(rect.GetSize()));
    m_ZoomSlider->Bind(wxEVT_SLIDER, &Editor::OnZoomChange, this);
}

Editor::~Editor()
{
}

void Editor::SetColour(int c)
{
    m_Canvas->SetColour(c);
    // m_CurrentColour->SetBackgroundColour(Utils::palette[c]);
}

bool Editor::Save(const wxString &filename)
{
    for (int i = 0; i < sprBase.nWidth; ++i)
    {
        for (int j = 0; j < sprBase.nHeight; ++j)
        {
            short colour = m_Sprite[j * sprBase.nWidth + i];

            if (colour == 16)
            {
                sprBase.SetColour(i, j, 0);
                sprBase.SetGlyph(i, j, L' ');
            }
            else
            {
                sprBase.SetColour(i, j, colour);
                sprBase.SetGlyph(i, j, 0x2588);
            }
        }
    }
    return sprBase.Save(filename.wc_str());
}

bool Editor::Open(const wxString &filename)
{
    if (!sprBase.Load(filename.wc_str()))
        return false;
    else
    {
        delete[] m_Sprite;
        m_Sprite = new unsigned char[sprBase.nWidth * sprBase.nHeight]{0};
        for (int i = 0; i < sprBase.nWidth; ++i)
        {
            for (int j = 0; j < sprBase.nHeight; ++j)
            {
                wchar_t glyph = sprBase.GetGlyph(i, j);
                short colour = sprBase.GetColour(i, j);

                if (glyph == L' ')
                {
                    m_Sprite[j * sprBase.nWidth + i] = 16;
                }
                else
                {
                    m_Sprite[j * sprBase.nWidth + i] = colour & 0x000F;
                }
            }
        }
        m_Canvas->SetSpriteData(sprBase.nHeight, sprBase.nWidth, m_Sprite);
        return true;
    }
}

bool Editor::New(int r, int c)
{
    delete[] m_Sprite;
    m_Sprite = new unsigned char[r * c]{0};
    m_Canvas->SetSpriteData(r, c, m_Sprite);
    sprBase = olc::olcSprite(c, r);
    return false;
}

void Editor::OnZoomChange(wxCommandEvent &event)
{
    m_StatusBar->SetStatusText(wxString("Zoom: ") << m_ZoomSlider->GetValue(), 2);
    m_Canvas->SetPixelSize(m_ZoomSlider->GetValue());
    event.Skip();
}
