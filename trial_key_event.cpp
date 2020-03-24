//
// Created by chendi on 2020/3/23.
//

#include <ncurses.h>

int main(int argc, char **argv)
{
    initscr();
    cbreak();
    printw("press any key to exit...");
    getch();
    endwin();
    return 0;
}