//
// Created by chendi on 2020/3/24.
//

#include "block_def.h"
#include <iostream>
#include <random>
#include <ncurses.h>
#include <string>

using namespace std;

Tetris_block::Tetris_block()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 6);  // c++11 random lib

    this->block_type = this->type_list[dis(gen)];
}

void Tetris_block::echo_type()
{
    char str[] = "The current block type is  ";
    str[sizeof(str) - 2] = this->block_type;
    mvprintw(max_row - 1, max_col / 2 - int(sizeof(str) / 2), str);
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
    for(int i = 0; i < this->map.size(); i++)
    {
        for(int j = 0; j < this->map[0].size(); j++)
            mvaddch(this->map_rel_row + i, this->map_rel_col + j,
                    this->map[i][j]);
    }
    refresh();
}