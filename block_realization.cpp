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
    this->core = {1, max_col / 2 - 5};

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
    mvaddch(this->core[0], this->core[1], '*');
    mvaddch(this->periphery[0][0], this->periphery[0][1], '*');
    mvaddch(this->periphery[1][0], this->periphery[1][1], '*');
    mvaddch(this->periphery[2][0], this->periphery[2][1], '*');
    refresh();
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
    mvprintw(0, max_col / 2 - int(sizeof(str1) / 2), str1);
    mvprintw(1, max_col / 2 - int(sizeof(str2) / 2), str2);
    refresh();
    getch();
    return true;
}