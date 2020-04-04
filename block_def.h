//
// Created by chendi on 2020/3/24.
//

#ifndef TETRIS_BLOCK_DEF_H
#define TETRIS_BLOCK_DEF_H

#include <iostream>
#include <vector>
using namespace std;
extern int max_row, max_col;

class Map
{
private:
    int map_rel_col, map_rel_row;

public:
    vector<vector<char>> map;
    Map();
    void plot_map();
};

class Tetris_block
{
private:
    char block_type{};
    char type_list[7] = {'J', 'L', 'I', 'O', 'Z', 'S', 'T'};
    vector<int> core;
    vector<vector<int>> periphery;

public:
    Tetris_block();
    void echo_type();
};

#endif //TETRIS_BLOCK_DEF_H
