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
    std::vector<int> last_shot;
    int* field[10];
    void set_priority(int shooting_res);
    std::vector<int> shoot();
    void dead_ship();
    int get_hit(std::vector<int> click);
    void set_field(int x, int y, int val);
    int get_field(int x, int y);
    Player(bool ai);
    std::vector<int> ships;
    std::vector<int> enemyships;
};
#endif
