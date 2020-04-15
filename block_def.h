//
// Created by chendi on 2020/3/24.
//

#ifndef TETRIS_BLOCK_DEF_H
#define TETRIS_BLOCK_DEF_H

#include <iostream>
#include <vector>
using namespace std;
extern int max_row, max_col;
bool welcome();

class Map
{
public:
    int map_rel_col, map_rel_row;
    vector<vector<char>> map;
    Map();
    void plot_map();
    void map_refresh();
};

class Tetris_block
{
private:
    char block_type{};
    char type_list[7] = {'J', 'L', 'I', 'O', 'Z', 'S', 'T'};

public:
    int rel_row, rel_col;
    vector<int> core;
    vector<vector<int>> periphery;
    Tetris_block(int row, int col);
    void echo_type();
    void plot_block();
    bool block_fall(Map * ptr);
    bool block_left(Map * ptr);
    bool block_right(Map * ptr);
    bool block_rotation(Map * ptr);
    void anti_clk_rot(Map * ptr);
    void clk_rot(Map * ptr);
};

bool game_over(Map * pmap, Tetris_block * pblk);

#endif //TETRIS_BLOCK_DEF_H
