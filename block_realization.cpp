//
// Created by chendi on 2020/3/24.
//

#include "block_def.h"
#include <iostream>
#include <random>

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
    cout << this->block_type << endl;
}