// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

class MyFrame : public wxFrame
{
public:
    MyFrame();

private:
    void OnPaint(wxPaintEvent &event);

    wxPanel *m_board;
    wxBitmap m_blackRook;
    wxBitmap m_blackKnight;
    wxBitmap m_blackBishop;
    wxBitmap m_blackQueen;
    wxBitmap m_blackKing;
    wxBitmap m_blackPawn;

    wxBitmap m_whiteRook;
};

MyFrame::MyFrame()
    : wxFrame(NULL, wxID_ANY, "Chess", wxDefaultPosition, wxSize(820, 840))
{
    m_board = new wxPanel(this, wxID_ANY);
    m_board->Bind(wxEVT_PAINT, &MyFrame::OnPaint, this);

    // Load the image.
    wxImage im("640px-Chess_Pieces_Sprite.svg.png", wxBITMAP_TYPE_PNG);

    // Extract the images of the pieces from the larger image.
    wxBitmap b(im);
    m_blackKing = b.GetSubBitmap(wxRect(5, 113, 100, 100));
    m_blackQueen = b.GetSubBitmap(wxRect(110, 113, 100, 100));
    m_blackBishop = b.GetSubBitmap(wxRect(215, 113, 100, 100));
    m_blackKnight = b.GetSubBitmap(wxRect(323, 113, 100, 100));
    m_blackRook = b.GetSubBitmap(wxRect(433, 113, 100, 100));
    m_blackPawn = b.GetSubBitmap(wxRect(535, 113, 100, 100));

    m_whiteRook = b.GetSubBitmap(wxRect(433, 13, 100, 100));
}

void MyFrame::OnPaint(wxPaintEvent &)
{
    wxPaintDC dc(m_board);
    dc.Clear();

    // Draw thie light squares
    dc.SetPen(wxColour(209, 139, 71));
    dc.SetBrush(wxColour(209, 139, 71));
    dc.DrawRectangle(0, 0, 800, 800);

    // Draw thie dark squares
    dc.SetPen(wxColour(255, 206, 158));
    dc.SetBrush(wxColour(255, 206, 158));
    for (int i = 0; i < 8; ++i)
    {
        for (int j = i % 2; j < 8; j += 2)
        {
            dc.DrawRectangle(i * 100, j * 100, 100, 100);
        }
    }

    // Draw thie black pieces
    dc.DrawBitmap(m_blackRook, 0, 0, true);
    dc.DrawBitmap(m_blackKnight, 100, 0, true);
    dc.DrawBitmap(m_blackBishop, 200, 0, true);
    dc.DrawBitmap(m_blackQueen, 300, 0, true);
    dc.DrawBitmap(m_blackKing, 400, 0, true);
    dc.DrawBitmap(m_blackBishop, 500, 0, true);
    dc.DrawBitmap(m_blackKnight, 600, 0, true);
    dc.DrawBitmap(m_blackRook, 700, 0, true);

    dc.DrawBitmap(m_whiteRook, 0, 713, true);

    for (int i = 0; i < 8; ++i)
    {
        dc.DrawBitmap(m_blackPawn, 100 * i, 100, true);
    }
}

class MyApp : public wxApp
{
public:
    virtual bool OnInit()
    {
        ::wxInitAllImageHandlers();
        MyFrame *frame = new MyFrame();
        frame->Show();
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
