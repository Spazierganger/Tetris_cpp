//
// Created by chendi on 2020/3/23.
//

#include <ncurses.h>

int main(int argc, char **argv)
{
    initscr();
    cbreak();
    noecho();
    refresh();
    printw("press any key\n");
    char c = getch();
    while(c != 'q')
    {
        refresh();
        printw("Press q for exit.\n");
        c = getch();
    }
    endwin();
    return 0;
}