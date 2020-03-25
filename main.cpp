#include <iostream>
#include <ncurses.h>
#include "block_def.h"
#include <string>
#include <vector>
using namespace std;

int max_row, max_col; // get the screen size from ncurses, global
vector<vector<int>> map;

int main()
{
    initscr();
    raw();
    getmaxyx(stdscr, max_row, max_col);  // 24, 80
    if(max_row < 22 || max_col < 24)
    {
        char str1[] = "Your screen is not big enough for the game!\n";
        char str2[] = "Press any key to exit.\n";
        mvprintw(0, max_col / 2 - int(sizeof(str1) / 2), str1);
        mvprintw(1, max_col / 2 - int(sizeof(str2) / 2), str2);
        refresh();
        getch();
        endwin();
        return 0;
    }

    noecho();
    char str1[] = "Welcome to the Tetris game!\n";
    char str2[] = "Press any key to start game!\n";
    mvprintw(0, max_col / 2 - int(sizeof(str1) / 2), str1);
    mvprintw(1, max_col / 2 - int(sizeof(str2) / 2), str2);
    refresh();
    getch();
//    auto *t1 = new Tetris_block();
//    (*t1).echo_type();
//    delete t1;

    map.push_back({ 0, max_col / 2 - 11}); // left upper point
    map.push_back({21, max_col / 2}); // right lower point
    erase();
    refresh();
    for(int i = map[0][1]; i <= map[1][1]; i++)
    {
        mvaddch(map[0][0], i, '#');
        mvaddch(map[1][0], i, '#');
    }
    for(int i = map[0][0]; i <= map[1][0]; i++)
    {
        mvaddch(i, map[0][1], '#');
        mvaddch(i, map[1][1], '#');
    }
    refresh();
    getch();
    endwin();
    return 0;
}