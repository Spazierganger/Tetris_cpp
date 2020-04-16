//
// Created by chendi on 2020/3/24.
//

#ifndef TETRIS_BLOCK_DEF_H
#define TETRIS_BLOCK_DEF_H

#include <iostream>
#include <vector>
using namespace std;
extern int max_row, max_col;
extern bool game_is_over;
bool welcome();
void bye();

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
    Tetris_block();
    void echo_type();
    void plot_block();
    bool block_fall();
    bool block_left();
    bool block_right();
    bool block_rotation();
    void anti_clk_rot();
    void clk_rot();
};

void auto_falling();
extern Map *pMap;
extern Tetris_block *pBlk;
bool game_over(Tetris_block *pblk=pBlk);

#endif //TETRIS_BLOCK_DEF_H
