#include <iostream>
#include <ncurses.h>
#include "block_def.h"
#include <string>
#include <vector>
#include <algorithm>
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
    Map *pMap;
    pMap = &my_map;
    my_map.plot_map();

    auto *t1 = new Tetris_block(my_map.map_rel_row, my_map.map_rel_col);
    (*t1).echo_type();
    (*t1).plot_block();
    char c = getch();
    while(c != 'z')
    {
        bool flag = true;
        switch(c)
        {
            case 'a':
                (*t1).block_left(pMap);
                break;
            case 's':
                if(!(*t1).block_fall(pMap))
                {
                    delete t1;
                    flag = false;
                }
                break;
            case 'd':
                (*t1).block_right(pMap);
                break;
            case 'w':
                (*t1).block_rotation(pMap);
                break;
            case 'q':
                (*t1).anti_clk_rot(pMap);
                break;
            case 'e':
                (*t1).clk_rot(pMap);
                break;
            default:
                ;
        }

        my_map.plot_map();
        refresh();
        if(!flag)
            break;
        (*t1).plot_block();
        refresh();
        c = getch();
    }

    getch();
    endwin();
    return 0;
}