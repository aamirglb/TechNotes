#include <wx/wx.h>
#include "widget.h"
#include "burning.h"

#include <array>

std::array<int, 9> num{75, 150, 225, 300, 375, 450, 525, 600, 675};

Widget::Widget(wxPanel *parent, int id) : wxPanel(parent, id, wxDefaultPosition, wxSize(-1, 30), wxBORDER_SUNKEN),
                                          m_Parent{parent}
{
    Bind(wxEVT_PAINT, &Widget::OnPaint, this);
    Bind(wxEVT_SIZE, &Widget::OnSize, this);
}

void Widget::OnPaint(wxPaintEvent &event)
{
    wxFont font(9, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                wxFONTWEIGHT_NORMAL, false, wxT("Courier 10 Pitch"));

    wxPaintDC dc(this);
    dc.SetFont(font);
    auto size = GetSize();
    int width = size.GetWidth();

    auto burn = static_cast<Burning *>(m_Parent->GetParent());
    auto currWidth = burn->GetCurWidth();
    auto step = static_cast<int>(std::round(width / 10.));

    auto till = static_cast<int>((width / 750.) * currWidth);
    auto full = static_cast<int>((width / 750.) * 700);

    if (currWidth >= 700)
    {
        dc.SetPen(wxPen(wxColor(255, 255, 184)));
        dc.SetBrush(wxBrush(wxColor(255, 255, 184)));
        dc.DrawRectangle(0, 0, full, 30);

        dc.SetPen(wxPen(wxColor(255, 175, 175)));
        dc.SetBrush(wxBrush(wxColor(255, 175, 175)));
        dc.DrawRectangle(full, 0, till - full, 30);
    }
    else
    {
        dc.SetPen(wxPen(wxColor(255, 255, 184)));
        dc.SetBrush(wxBrush(wxColor(255, 255, 184)));
        dc.DrawRectangle(0, 0, till, 30);
    }

    dc.SetPen(wxPen(wxColor(90, 80, 60)));

    for (int i = 1; i <= num.size(); ++i)
    {
        dc.DrawLine(i * step, 0, i * step, 6);
        auto size = dc.GetTextExtent(wxString::Format(wxT("%d"), num[i - 1]));
        dc.DrawText(wxString::Format(wxT("%d"), num[i - 1]), i * step - size.GetWidth() / 2, 8);
    }
}

void Widget::OnSize(wxSizeEvent &event)
{
    Refresh();
}