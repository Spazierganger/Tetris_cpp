//
// Created by chendi on 2020/3/24.
//

#include "block_def.h"
#include <iostream>
#include <random>
#include <ncurses.h>
#include <string>
#include <algorithm>
#include <thread>
#include <chrono>

using namespace std;

Tetris_block::Tetris_block()
{
    int row{(*pMap).map_rel_row};
    int col{(*pMap).map_rel_col};
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 6);  // c++11 random lib

    this->block_type = this->type_list[dis(gen)];
    this->core = {1, 5};
    this->rel_row = row;
    this->rel_col = col;

    vector<int> vec;
    switch(this->block_type)
    {
        case 'J' :
            vec = {this->core[0], this->core[1] - 2};
            this->periphery.push_back(vec);
            vec = {this->core[0], this->core[1] - 1};
            this->periphery.push_back(vec);
            vec = {this->core[0] + 1, this->core[1]};
            this->periphery.push_back(vec);
            break;
        case 'L' :
            vec = {this->core[0], this->core[1] + 2};
            this->periphery.push_back(vec);
            vec = {this->core[0], this->core[1] + 1};
            this->periphery.push_back(vec);
            vec = {this->core[0] + 1, this->core[1]};
            this->periphery.push_back(vec);
            break;
        case 'I' :
            vec = {this->core[0], this->core[1] + 2};
            this->periphery.push_back(vec);
            vec = {this->core[0], this->core[1] + 1};
            this->periphery.push_back(vec);
            vec = {this->core[0], this->core[1] - 1};
            this->periphery.push_back(vec);
            break;
        case 'O' :
            vec = {this->core[0] + 1, this->core[1]};
            this->periphery.push_back(vec);
            vec = {this->core[0], this->core[1] + 1};
            this->periphery.push_back(vec);
            vec = {this->core[0] + 1, this->core[1] + 1};
            this->periphery.push_back(vec);
            break;
        case 'Z' :
            vec = {this->core[0], this->core[1] - 1};
            this->periphery.push_back(vec);
            vec = {this->core[0] + 1, this->core[1]};
            this->periphery.push_back(vec);
            vec = {this->core[0] + 1, this->core[1] + 1};
            this->periphery.push_back(vec);
            break;
        case 'S' :
            vec = {this->core[0], this->core[1] + 1};
            this->periphery.push_back(vec);
            vec = {this->core[0] + 1, this->core[1]};
            this->periphery.push_back(vec);
            vec = {this->core[0] + 1, this->core[1] - 1};
            this->periphery.push_back(vec);
            break;
        case 'T' :
            vec = {this->core[0], this->core[1] + 1};
            this->periphery.push_back(vec);
            vec = {this->core[0], this->core[1] - 1};
            this->periphery.push_back(vec);
            vec = {this->core[0] + 1, this->core[1]};
            this->periphery.push_back(vec);
            break;
    }
    game_over(this);
}

void Tetris_block::echo_type()
{
    char str[] = "block type  ";
    str[sizeof(str) - 2] = this->block_type;
    mvprintw(1, max_col / 2 + 1, str);
    refresh();
}

void Tetris_block::plot_block()
{
    mvaddch(this->rel_row + this->core[0],
            this->rel_col + this->core[1], '*');
    mvaddch(this->rel_row + this->periphery[0][0],
            this->rel_col + this->periphery[0][1], '*');
    mvaddch(this->rel_row + this->periphery[1][0],
            this->rel_col + this->periphery[1][1], '*');
    mvaddch(this->rel_row + this->periphery[2][0],
            this->rel_col + this->periphery[2][1], '*');
    refresh();
}

bool Tetris_block::block_fall()
{
    vector<vector<char >> map = (*pMap).map;
    this->core[0] += 1;
    this->periphery[0][0] += 1;
    this->periphery[1][0] += 1;
    this->periphery[2][0] += 1;

    if(map[this->core[0]][this->core[1]] == '#' ||
    map[this->periphery[0][0]][this->periphery[0][1]] == '#' ||
    map[this->periphery[1][0]][this->periphery[1][1]] == '#' ||
    map[this->periphery[2][0]][this->periphery[2][1]] == '#')
    {
        this->core[0] -= 1;
        this->periphery[0][0] -= 1;
        this->periphery[1][0] -= 1;
        this->periphery[2][0] -= 1;

        // refresh map if block is down to the ground
        map[this->core[0]][this->core[1]] = '#';
        map[this->periphery[0][0]][this->periphery[0][1]] = '#';
        map[this->periphery[1][0]][this->periphery[1][1]] = '#';
        map[this->periphery[2][0]][this->periphery[2][1]] = '#';
        (*pMap).map = map;
        (*pMap).map_refresh();
        return false;
    }
    return true;
}

bool Tetris_block::block_left()
{
    this->core[1] -= 1;
    this->periphery[0][1] -= 1;
    this->periphery[1][1] -= 1;
    this->periphery[2][1] -= 1;

    vector<vector<char >> map = (*pMap).map;
    if(map[this->core[0]][this->core[1]] == '#' ||
       map[this->periphery[0][0]][this->periphery[0][1]] == '#' ||
       map[this->periphery[1][0]][this->periphery[1][1]] == '#' ||
       map[this->periphery[2][0]][this->periphery[2][1]] == '#')
    {
        this->core[1] += 1;
        this->periphery[0][1] += 1;
        this->periphery[1][1] += 1;
        this->periphery[2][1] += 1;
        return false;
    }
    return true;
}

bool Tetris_block::block_right()
{
    this->core[1] += 1;
    this->periphery[0][1] += 1;
    this->periphery[1][1] += 1;
    this->periphery[2][1] += 1;

    vector<vector<char >> map = (*pMap).map;
    if(map[this->core[0]][this->core[1]] == '#' ||
       map[this->periphery[0][0]][this->periphery[0][1]] == '#' ||
       map[this->periphery[1][0]][this->periphery[1][1]] == '#' ||
       map[this->periphery[2][0]][this->periphery[2][1]] == '#')
    {
        this->core[1] -= 1;
        this->periphery[0][1] -= 1;
        this->periphery[1][1] -= 1;
        this->periphery[2][1] -= 1;
        return false;
    }
    return true;
}

bool Tetris_block::block_rotation()
{
    if(this->block_type == 'O')
        return true;

    vector<vector<char >> map = (*pMap).map;

    // try to rotate along one point as the centroid, if failed, try another
    vector<vector<int>> center;
    center.push_back(this->core);
    for(int i = 0; i < 3; i ++)
        center.push_back(this->periphery[i]);

    // try rotate anti-clockwise with every centroid
    int pre;
    for(int i = 0; i < 4; i++)
    {
        pre = this->core[0];
        this->core[0] = center[i][0] - (this->core[1] - center[i][1]);
        this->core[1] = center[i][1] - (center[i][0] - pre);

        for(int j = 0; j < 3; j++)
        {
            pre = this->periphery[j][0];
            this->periphery[j][0] = center[i][0] - (this->periphery[j][1] - center[i][1]);
            this->periphery[j][1] = center[i][1] - (center[i][0] - pre);
        }

        bool index_top = min({this->core[0], this->periphery[0][0],
                              this->periphery[1][0], this->periphery[2][0]}) > 0;
        bool index_left = min({this->core[1], this->periphery[0][1],
                               this->periphery[1][1], this->periphery[2][1]}) > 0;
        bool index_bot = max({this->core[0], this->periphery[0][0],
                              this->periphery[1][0], this->periphery[2][0]}) < 21;
        bool index_right = max({this->core[1], this->periphery[0][1],
                                this->periphery[1][1], this->periphery[2][1]}) < 11;
        bool collision = map[this->core[0]][this->core[1]] == '#' ||
                         map[this->periphery[0][0]][this->periphery[0][1]] == '#' ||
                         map[this->periphery[1][0]][this->periphery[1][1]] == '#' ||
                         map[this->periphery[2][0]][this->periphery[2][1]] == '#';

        if(index_top && index_left && index_right && index_bot && !collision)
            return true;
        else
        {
            // rotate clockwise back
            pre = this->core[0];
            this->core[0] = center[i][0] - (center[i][1] - this->core[1]);
            this->core[1] = center[i][1] + (center[i][0] - pre);

            for(int j = 0; j < 3; j++)
            {
                pre = this->periphery[j][0];
                this->periphery[j][0] = center[i][0] - (center[i][1] - this->periphery[j][1]);
                this->periphery[j][1] = center[i][1] + (center[i][0] - pre);
            }
        }
    }
    return false;
}

void Tetris_block::anti_clk_rot()
{
    // primary version, doesn't consider collision or index out of range problem.
    int pre;

    for(int j = 0; j < 3; j++)
    {
        pre = this->periphery[j][0];
        this->periphery[j][0] = this->core[0] - (this->periphery[j][1] - this->core[1]);
        this->periphery[j][1] = this->core[1] - (this->core[0] - pre);
    }
}

void Tetris_block::clk_rot()
{
    int pre;

    for(int j = 0; j < 3; j++)
    {
        pre = this->periphery[j][0];
        this->periphery[j][0] = this->core[0] - (this->core[1] - this->periphery[j][1]);
        this->periphery[j][1] = this->core[1] + (this->core[0] - pre);
    }
}

Map::Map()
{
    this->map_rel_col = max_col / 2 - 11;
    this->map_rel_row = 0;

    vector<char> vec1 = {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'};
    vector<char> vec2 = {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'};
    this->map.push_back(vec1);
    for(int i = 0; i < 20; i++)
        this->map.push_back(vec2);
    this->map.push_back(vec1);
}

void Map::plot_map()
{
    erase();
    refresh();
    for(unsigned long i = 0; i < this->map.size(); i++)
    {
        for(unsigned long j = 0; j < this->map[0].size(); j++)
            mvaddch(this->map_rel_row + i, this->map_rel_col + j,
                    this->map[i][j]);
    }
    refresh();
}

void Map::map_refresh()
{
    bool filled;
    vector<char> blank_line = {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'};
    for(auto row = this->map.end() - 2; row != this->map.begin(); row --)
    {
        filled = true;
        for(char & col : (*row))
        {
            if(col == ' ')
            {
                filled = false;
                break;
            }
        }
        if(filled)
        {
            row = this->map.erase(row);
            this->map.insert(this->map.begin() + 1, blank_line);
            row += 1;  // or the iterator will miss one element
        }
    }
}

bool welcome()
{
    if(max_row < 22 || max_col < 24)
    {
        char str1[] = "Your screen is not big enough for the game!\n";
        char str2[] = "Press any key to exit.\n";
        mvprintw(0, max_col / 2 - int(sizeof(str1) / 2), str1);
        mvprintw(1, max_col / 2 - int(sizeof(str2) / 2), str2);
        refresh();
        getch();
        endwin();
        return false;
    }

    char str1[] = "Welcome to the Tetris game!\n";
    char str2[] = "Press any key to start game!\n";
    char str3[] = "Game Play\n";
    char str4[] = "W: rotate\n";
    char str5[] = "S: accelerate the fall\n";
    char str6[] = "A: move left\n";
    char str7[] = "D: move right\n";
    mvprintw(0, max_col / 2 - int(sizeof(str1) / 2), str1);
    mvprintw(1, max_col / 2 - int(sizeof(str2) / 2), str2);
    mvprintw(3, max_col / 2 - int(sizeof(str3) / 2), str3);
    mvprintw(4, max_col / 2 - int(sizeof(str4) / 2), str4);
    mvprintw(5, max_col / 2 - int(sizeof(str5) / 2), str5);
    mvprintw(6, max_col / 2 - int(sizeof(str6) / 2), str6);
    mvprintw(7, max_col / 2 - int(sizeof(str7) / 2), str7);
    refresh();
    getch();
    return true;
}

bool game_over(Tetris_block * pblk)
{
    vector<vector<char>> map = (*pMap).map;

    if (map[(*pblk).core[0]][(*pblk).core[1]] == '#' ||
            map[(*pblk).periphery[0][0]][(*pblk).periphery[0][1]] == '#' ||
            map[(*pblk).periphery[1][0]][(*pblk).periphery[1][1]] == '#' ||
            map[(*pblk).periphery[2][0]][(*pblk).periphery[2][1]] == '#')
    {
        // end the thread
        game_is_over = true;
        return true;
    }
    return false;
}

void auto_falling()
{
    curs_set(0);
    while (!game_is_over)
    {
        if(!(*pBlk).block_fall())
        {
            pBlk = new Tetris_block();
        }
        (*pMap).plot_map();
        (*pBlk).plot_block();
        refresh();
        this_thread::sleep_for(chrono::milliseconds(700));
    }
}

void bye()
{
    erase();
    char gameover[] = "Game Over!\n";
    char goodbye[] = "Press any key to exit.\n";
    mvprintw(0, max_col / 2 - int(sizeof(gameover) / 2), gameover);
    mvprintw(1, max_col / 2 - int(sizeof(goodbye) / 2), goodbye);
    refresh();
    timeout(-1);  // unset the timeout gap, always wait for input
    getch();
    endwin();
}