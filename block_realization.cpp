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