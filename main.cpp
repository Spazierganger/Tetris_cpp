#include <iostream>
#include <ncurses.h>
#include "block_def.h"
#include <string>
#include <vector>
using namespace std;

int max_row, max_col; // get the screen size from ncurses, global

int main()
{
    initscr();
    raw();
    noecho();
    getmaxyx(stdscr, max_row, max_col);  // 24, 80

    if(!welcome())  // too small screen
        return 0;

    Map my_map;
    my_map.plot_map();

    auto *t1 = new Tetris_block();
    (*t1).echo_type();
    (*t1).plot_block();
    delete t1;

    getch();
    endwin();
    return 0;
}