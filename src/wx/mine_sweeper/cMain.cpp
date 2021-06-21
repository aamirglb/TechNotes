#include "cMain.h"
#include <iostream>
#include <curses.h>


// wxBEGIN_EVENT_TABLE(cMain, wxFrame)
// 	EVT_BUTTON(10001, OnButtonClicked)
// wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, 
    wxID_ANY, 
    "Mine Sweeper", 
    wxPoint(30, 30), 
    wxSize(800, 600))
{
    wxFont font(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);

    btn = new wxButton*[nFieldWidth * nFieldHeight];
    label = new wxStaticText(this, wxID_ANY, "Score: 0/70");
    label->SetFont(font);

    wxGridSizer* grid = new wxGridSizer(nFieldWidth + 1, nFieldHeight, 0, 0);
    

    nField = new int[nFieldWidth * nFieldHeight];
    

    for (auto x = 0; x < nFieldWidth; ++x) {
        for (auto y = 0; y < nFieldHeight; ++y) {
            //btn[y * nFieldWidth + x] = new wxButton(this, 1000 + (y * nFieldWidth + x), wxString::Format(wxT("%d"), (int)(y * nFieldWidth + x)));
            btn[y * nFieldWidth + x] = new wxButton(this, 1000 + (y * nFieldWidth + x));
            btn[y * nFieldWidth + x]->SetFont(font);
            grid->Add(btn[y * nFieldWidth + x], 1, wxEXPAND | wxALL);
            // Bind event handler
            btn[y * nFieldWidth + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnButtonClicked, this);
            nField[y * nFieldWidth + x] = 0;
        }
    }

    grid->Add(label, wxEXPAND | wxALL);
    this->SetSizer(grid);
    grid->Layout();

    //m_btn1 = new wxButton(this,
    //	10001,
    //	"Click Me",
    //	wxPoint(10, 10),
    //	wxSize(150, 50));

    //m_txt1 = new wxTextCtrl(this,
    //	wxID_ANY,
    //	"",
    //	wxPoint(10, 70),
    //	wxSize(300, 30));

    //m_list1 = new wxListBox(this,
    //	wxID_ANY,
    //	wxPoint(10, 110),
    //	wxSize(300, 300));

    // Initialise curses
    initscr();
    raw();
    curs_set(0);
    // printw("Hello World !!!");
    refresh();
}

cMain::~cMain()
{
    delete[]btn;
    endwin();
}

void cMain::PrintSheetCode()
{
    for (auto i = 0; i < (3 * nFieldWidth); ++i)
        printw("=");
    printw("\n");
        // std::cout << "=";
    // std::cout << '\n';

    for (auto i = 0; i < nFieldWidth; ++i) {
        for (auto j = 0; j < nFieldHeight; ++j) {
            if (nField[j * nFieldWidth + i] == -1) {
                // std::cout << " X ";
                printw(" X ");
            }
            else {
                printw(" . ");
                // std::cout << " . ";
            }
        }
        printw("\n");
        // std::cout << "\n";
    }
    for (auto i = 0; i < (3 * nFieldWidth); ++i)
        printw("*");
        // std::cout << "*";
    // std::cout << '\n';
    printw("\n");
    refresh();
}

void cMain::OnButtonClicked(wxCommandEvent& evt)
{
    //m_list1->AppendString(m_txt1->GetValue());
    int x = (evt.GetId() - 1000) % nFieldWidth;
    int y = (evt.GetId() - 1000) / nFieldWidth;
    move(0, 0);
    printw("(%d, %d)\n", x, y);
    refresh();
    wxString msg;
    msg.Printf("Position (%d, %d) clicked\n", x, y);
    if (bFirstClick) {
        int mines = 30;

        while (mines) {
            int rx = rand() % nFieldWidth;
            int ry = rand() % nFieldHeight;

            if (nField[ry * nFieldWidth + rx] == 0 && rx != x && ry != y) {
                wxString msg;
                //msg.Printf(wxT("Putting a mine at location (%d, %d)"), rx, ry);
                //std::cout << msg.c_str() << '\n';
                nField[ry * nFieldWidth + rx] = -1;
                --mines;
            }
        }
        PrintSheetCode();
        bFirstClick = false;
    }

    btn[y * nFieldWidth + x]->Enable(false);
    
    if (prevX != -1 || prevY != -1) {
        btn[prevY * nFieldWidth + prevX]->SetBackgroundColour(wxNullColour);
        // btn[nPrevButton]->SetBackgroundStyle(wxBG_STYLE_SYSTEM);
        for (int i = -1; i < 2; ++i) {
            for (int j = -1; j < 2; ++j) {
                if (prevX + i >= 0 && prevX + i < nFieldWidth && prevY + j >= 0 && prevY + j < nFieldHeight) {
                    btn[(prevY + j) * nFieldWidth + (prevX + i)]->SetBackgroundColour(wxNullColour);

                    // Update console also
                    move(2+prevX, (3*prevY));
                    attron(A_NORMAL);
                    if (nField[j * nFieldWidth + i] == -1) {
                        printw(" X ");
                    } else {
                        printw(" . ");
                    }
                    attroff(A_NORMAL);
                    refresh();
                }
            }
        }
    }

    if (nField[y * nFieldWidth + x] == -1) {
        wxString msg;
        msg.Printf("BOOOOM !! - Game Over :(-\nYour Score is %d/70", nScore);
        wxMessageBox(msg);

        // Reset game
        resetGame();
    }
    else {
        // count neighbouring mines
        int mine_count = 0;
        for (int i = -1; i < 2; ++i) {
            for (int j = -1; j < 2; ++j) {
                if (x + i >= 0 && x + i < nFieldWidth && y + j >= 0 && y + j < nFieldHeight) {
                    if (nField[(y + j) * nFieldWidth + (x + i)] == -1)
                        ++mine_count;

                    // set the background of neigbouring cell to yellow
                    if(btn[(y + j) * nFieldWidth + (x + i)]->GetLabel() == "")
                        btn[(y + j) * nFieldWidth + (x + i)]->SetBackgroundColour(*wxCYAN);
                }
            }
        }

        // if (mine_count > 0) {
            btn[y * nFieldWidth + x]->SetLabel(std::to_string(mine_count));
            btn[y * nFieldWidth + x]->Enable(false);
        // }
        btn[y * nFieldWidth + x]->SetBackgroundColour(*wxBLUE);
        ++nScore;

        if(nScore == 70) {
            wxMessageBox("Congratulations!! You Won.");
            resetGame();
            return;
        }
        // move(2, (3*x)+1);
        // printw("%d", (3*x));
        move(2+x, (3*y));
        attron(A_BLINK | A_REVERSE | A_BOLD);
        printw(" . ");
        attroff(A_BLINK | A_REVERSE | A_BOLD);
        refresh();
    }
    
    

    prevY = y;
    prevX = x;
    
    wxString score;
    score.Printf("Score: %d/70", nScore);
    label->SetLabel(score);
    evt.Skip();
}

void cMain::resetGame() {
    bFirstClick = true;
    nScore = 0;
    for (int x = 0; x < nFieldWidth; ++x) {
        for (int y = 0; y < nFieldHeight; ++y) {
            nField[y * nFieldWidth + x] = 0;
            btn[y * nFieldWidth + x]->SetLabel("");
            btn[y * nFieldWidth + x]->Enable(true);
        }
    }
    clear();
}