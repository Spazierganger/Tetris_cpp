#include <iostream>
#include <ncurses.h>
#include "block_def.h"
#include <string>
#include <vector>
#include <algorithm>
#include <thread>
using namespace std;

int max_row, max_col; // get the screen size from ncurses, global

int main()
{
    initscr();
    raw();
    noecho();
    getmaxyx(stdscr, max_row, max_col);  // 24, 80

    if(!welcome())  // too small screen
        return -1;

    Map my_map;
    Map *pMap;
    pMap = &my_map;
    my_map.plot_map();

    Tetris_block *pBlk;
    Tetris_block block(my_map.map_rel_row, my_map.map_rel_col);
    pBlk = &block;
//    thread t_fall(auto_falling(pMap, pBlk));
//    t_fall.detach();

    while(true)
    {
        if(game_over(pMap, pBlk))
            break;

        block.plot_block();
        char c = getch();
        switch(c)
        {
            case 'a':
                block.block_left(pMap);
                break;
            case 's':
                block.block_fall(pMap);
                break;
            case 'd':
                block.block_right(pMap);
                break;
            case 'w':
                block.block_rotation(pMap);
                break;
            case 'q':
                block.anti_clk_rot(pMap);
                break;
            case 'e':
                block.clk_rot(pMap);
                break;
            default:
                ;
        }

        my_map.plot_map();
        block.plot_block();
        refresh();
    }

    endwin();
    return 0;
}