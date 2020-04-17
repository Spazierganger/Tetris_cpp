#include <iostream>
#include <ncurses.h>
#include "block_def.h"
#include <string>
#include <vector>
#include <algorithm>
#include <thread>
using namespace std;

int max_row, max_col; // get the screen size from ncurses, global
int score{0};
bool game_is_over{false};
Map *pMap;
Tetris_block *pBlk;

int main()
{
    initscr();
    raw();
    noecho();
    getmaxyx(stdscr, max_row, max_col);  // 24, 80

    timeout(-1);
    if(!welcome())  // too small screen
        return -1;

    timeout(100);  // wait 100 ms, if no input, timeout

    pMap = new Map();
    pBlk = new Tetris_block();
    thread t_fall(auto_falling);
    t_fall.detach();

    while(true)
    {
        if(game_is_over)
//        if(game_is_over)
        {
            if(t_fall.joinable())
                t_fall.join();  // let thread finish first
            break;
        }

        char c = getch();
        switch(c)
        {
            case 'a':
                (*pBlk).block_left();
                break;
            case 's':
                if(!(*pBlk).block_fall())
                {
                    char next_type{(*pBlk).get_next_type()};
                    delete pBlk;
                    pBlk = new Tetris_block(next_type);
                }
                break;
            case 'd':
                (*pBlk).block_right();
                break;
            case 'w':
                (*pBlk).block_rotation();
                break;
            case 'q':
                game_is_over = true;
            default:
                ;
        }

        (*pMap).plot_map();
        (*pBlk).plot_block();
        show_details();
        refresh();
    }

    bye();
    endwin();
    return 0;
}