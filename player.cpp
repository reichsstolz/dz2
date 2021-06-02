#include "headers/player.h"

Player::Player(bool ai) {
    is_ai=ai;
    ships_set=false;
    ships.resize(10);
    ships={11, 12, 13, 14, 21, 22, 23, 31, 32, 41};
}
bool Player::set_ships(int clickx, int  clicky) {
    std::vector<int> click(map.capture_click(clickx, clicky));

    if (ships.empty()){
        for (int i=0; i<10; i++){
            for (int k=0; k<10; k++){
                if (map.field[i][k]==2)
                    map.field[i][k]=0;
            }
        }
        ships_set=true;

        for(auto i: map.ships){
            ships.push_back(i->index);
        }
    }

    if (is_ai and !ships_set){
         ships_set=true;

    }else if (!ships_set and !click.empty()) {

        if (!map.hits.empty()){

            for (int i=0; i<ships.size(); i++) {

                if (ships[i] / 10 ==  click[0] - map.hits[0].hitx or ships[i] / 10 ==  click[1] - map.hits[0].hity and map.field[click[0]][click[1]]==0){
                    //std::cout<<"\nIndex "<<ships[i]<<" /10 "<<ships[i] / 10<<" X "<<map.hits[0].hitx - click[0]<<"  Y "<<map.hits[0].hity - click[1]<<"\n";
                    map.add_ship(Ship(ships[i]/10, bool(map.hits[0].hitx - click[0]), ships[i]), map.hits[0].hitx, map.hits[0].hity);
                    ships.erase(ships.begin() + i);
                    map.dead_ship(map.ships.back()->shipx, map.ships.back()->shipy, map.ships.back()->vertical, map.ships.back()->parts);
                    map.hits.clear();
                    break;
                }
            }

        }else if (map.field[click[0]][click[1]]==0){
            map.shoot(click[0], click[1]);
        }
    }
}

std::vector<int> Player::shoot() {

}

void Player::get_hit(int clickx, int clicky) {
    std::vector<int> click(map.capture_click(clickx, clicky));
    if (!click.empty()) {
        map.shoot(click[0], click[1]);
    }
}