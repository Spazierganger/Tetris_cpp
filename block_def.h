//
// Created by chendi on 2020/3/24.
//

#ifndef TETRIS_BLOCK_DEF_H
#define TETRIS_BLOCK_DEF_H

#include <iostream>

class Tetris_block
{
private:
    char block_type{};
    char type_list[7] = {'J', 'L', 'I', 'O', 'Z', 'S', 'T'};

public:
    Tetris_block();
    void echo_type();
};

#endif //TETRIS_BLOCK_DEF_H
