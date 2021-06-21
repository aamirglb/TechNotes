#include <ncurses.h>

int main()
{    
    int ch;

    initscr();            /* Start curses mode         */
    raw();                /* Line buffering disabled    */
    keypad(stdscr, TRUE);        /* We get F1, F2 etc..        */
    noecho();            /* Don't echo() while we do getch */

    printw("Hello World !!!\n");
    printw("World of Hello\n");
    move(0, 0);
    attron(A_BOLD | A_BLINK);
    printw("%c", 'H');
    attroff(A_BOLD | A_BLINK);

    move(1, 0);
    attron(A_BOLD | A_BLINK);
    printw("%c", 'W');
    attroff(A_BOLD | A_BLINK);
    
    refresh();            /* Print it on to the real screen */
    getch();            /* Wait for user input */
    endwin();            /* End curses mode          */

    return 0;
}