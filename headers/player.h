#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <cmath>
#include "map.h"
#include "ship.h"
class Player{
public:
    Map map;
    bool game_over;
    bool ships_set;
    bool is_ai;
    bool set_ships(int clickx, int clicky);
    int* field[10];
    //void set_priority();
    std::vector<int> shoot();
    void get_hit(int clickx, int clicky);
    Player(bool ai);
    std::vector<int> ships;
};
#endif
