#include "headers/player.h"

Player::Player(bool ai) {
    is_ai = ai;
    ships_set = false;
    game_over = false;
    std::srand(std::time(nullptr));
    ships.resize(10);
    last_shot.resize(2);
    ships={11, 12, 13, 14, 21, 22, 23, 31, 32, 41};
    //enemyships={1, 1, 1, 1, 2, 2, 2, 3, 3, 4};
    for (auto & i : field){
        i = new int[10];
        for (int k=0; k<10; k++){
            i[k] = 1;
        }
    }
}
bool Player::set_ships(int clickx, int  clicky) {
    std::vector<int> click(map.capture_click(clickx, clicky));

    if (ships.empty()){
        for (auto & i : map.field){
            for (int k=0; k<10; k++){
                if (i[k] == 2)
                    i[k] = 0;
            }
        }
        ships_set=true;

        for(auto i: map.ships){
            ships.push_back(i->index);
        }
    }

    if (is_ai and !ships_set){
         ships_set=true;
         map.set_ships(std::time(nullptr));//std::time(nullptr));

    }else if (!ships_set and !click.empty()) {

        if (!map.hits.empty()){

            for (int i=0; i<ships.size(); i++) {

                if ((ships[i] / 10 ==  click[0] - map.hits[0].hitx or ships[i] / 10 ==  click[1] - map.hits[0].hity) and map.field[click[0]][click[1]]==0){
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
    int max=-1;
    std::vector<std::vector<int>> possible_shots;
    for (auto & i : field){
       if (max<*std::max_element(i,i+10)){
            max=*std::max_element(i,i+10);
       }
    }
    for (int i=0; i<10; i++){
        for (int k=0; k<10; k++){
            if (field[i][k]==max) {
                //last_shot={i , k};
                //return {i, k};
                possible_shots.push_back({i, k});
            }
        }
    }
    last_shot=possible_shots[std::rand()%possible_shots.size()];
    return last_shot;

}

int Player::get_hit(std::vector<int> click) {
    //std::vector<int> click(map.capture_click(clickx, clicky));
    if (!click.empty()) {
        int val=map.shoot(click[0], click[1]);
        if (val==1){
            return 1;
        }
        for (int i=0; i<10 && bool(val);  i++){
            if (ships[i]==val){
                ships.erase(ships.begin()+i);
                if (ships.empty()){
                    game_over = true;
                }
                return 2;
            }
        }
        return 0;
    }
}
void Player::dead_ship(){
    for (int i=0; i<10; i++){
        for (int k=0; k<10; k++){
            if (field[i][k]==4) {
                field[i][k]=0;
                for (int j=i-1; j<i+2; j++){
                    for (int p=k-1; p<k+2; p++){
                        set_field(j, p, 0);
                    }
                }
            }
        }
    }
}

void Player::set_field(int x, int y, int val){
    if (x>-1 and y>-1 and y<10 and x<10){
        if(field[x][y]!=4 and field[x][y]!=0) field[x][y]=val;
    }
}
int Player::get_field(int x, int y){
    if (x>-1 and y>-1 and y<10 and x<10){
        return field[x][y];
    }else{
        return -1;
    }
}

void Player::set_priority(int shot_res) {
    int up;
    int down;
    if (shot_res == 0){
        field[last_shot[0]][last_shot[1]] = 0;
    }

    if(shot_res==2){
        dead_ship();
    }

    if (shot_res==1){
        field[last_shot[0]][last_shot[1]] = 4;
        if (field[last_shot[0]-1] [last_shot[1]] == 4 or field[last_shot[0]+1][last_shot[1]] == 4){
            up=last_shot[0]+1;
            down=last_shot[0]-1;
            while(up!=-5 or down!=-5){
                if (get_field(up, last_shot[1])==4){
                    set_field(up, last_shot[1]+1,  0);
                    set_field(up, last_shot[1]-1,  0);
                    up+=1;
                }else if (get_field(up, last_shot[1])==1){
                    set_field(up, last_shot[1], 5);
                    up=-5;
                }else{
                    up=-5;
                }
                if (get_field(down, last_shot[1])==4){
                    set_field(down, last_shot[1]+1,  0);
                    set_field(down, last_shot[1]-1,  0);
                    down-=1;
                }else if (get_field(down, last_shot[1])==1){
                    set_field(down, last_shot[1], 5);
                    down=-5;
                }else{
                    down=-5;
                }
            }

        }else if (field[last_shot[0]] [last_shot[1]-1] == 4 or field[last_shot[0]][last_shot[1]+1] == 4){
            up=last_shot[1]+1;
            down=last_shot[1]-1;
            while(up!=-5 or down!=-5){
                if (get_field(last_shot[0], up)==4){
                    set_field(last_shot[0]+1, up,   0);
                    set_field(last_shot[0]-1, up,   0);
                    up+=1;
                }else if (get_field(up, last_shot[1])==1){
                    set_field(last_shot[0], up,  5);
                    up=-5;
                }else{
                    up=-5;
                }
                if (get_field(last_shot[0], down)==4){
                    set_field(last_shot[0]+1, down,   0);
                    set_field(last_shot[0]-1, down,   0);
                    down+=1;
                }else if (get_field(last_shot[0], down)==1){
                    set_field(last_shot[0], down,  5);
                    down=-5;
                }else{
                    down=-5;
                }
            }

        }else{
            //set_field(last_shot[0], last_shot[1], get_field(last_shot[0], last_shot[1])*5);
            set_field(last_shot[0], last_shot[1]+1, get_field(last_shot[0], last_shot[1]+1)*5);
            set_field(last_shot[0]+1, last_shot[1], get_field(last_shot[0]+1, last_shot[1])*5);
            set_field(last_shot[0]-1, last_shot[1], get_field(last_shot[0]-1, last_shot[1])*5);
            set_field(last_shot[0], last_shot[1]-1, get_field(last_shot[0], last_shot[1]-1)*5);
        }
    }
    for (int i=0; i<10; i++){
        std::cout<<"\n";
        for (int k=0; k<10; k++) {
            std::cout<<field[k][i]<<" ";
        }
        }
}