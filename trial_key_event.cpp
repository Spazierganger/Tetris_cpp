//
// Created by chendi on 2020/3/23.
//

#include <ncurses.h>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    initscr();
    int row, col;
    getmaxyx(stdscr,row,col);
    printw("Row = %d, Col = %d\n");
    raw();
    noecho();
    refresh();
    printw("press any key\n");
    char c = getch();
    while(c != 'q')
    {
        printw("Press q to exit!\n");
        c = getch();
        refresh();
    }
    endwin();
    return 0;
}