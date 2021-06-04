#include "headers/map.h"
// compile g++ map.cpp test.cpp headers/map.h -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
void Map::set(int posx, int posy){
      for (auto & i : field){
          i= new int[10];
          for (int k=0; k<10; k++){
              i[k]=0;
          }
      }
      map_quads.setPrimitiveType(sf::LineStrip);
      map_quads.resize(56);
      posx+=50;
      int k=0;
      map_quads[0].position = sf::Vector2f(posx-50, posy);
      map_quads[0].color = sf::Color::Green;
      map_quads[1].position = sf::Vector2f(posx+450, posy);
      map_quads[1].color = sf::Color::Green;
      map_quads[2].position = sf::Vector2f(posx+450, posy+500);
      map_quads[2].color = sf::Color::Green;
      map_quads[3].position = sf::Vector2f(posx-50, posy+500);
      map_quads[3].color = sf::Color::Green;
      map_quads[4].position = sf::Vector2f(posx-50, posy);
      map_quads[4].color = sf::Color::Green;
      k+=5;
      for (size_t i=0; i!=500; i+=100){
        map_quads[k].position = sf::Vector2f(posx+i-50, posy);
        map_quads[k].color = sf::Color::Green;
        map_quads[k+1].position = sf::Vector2f(posx+i, posy);
        map_quads[k+1].color = sf::Color::Green;
        map_quads[k+2].position = sf::Vector2f(posx+i, posy+500);
        map_quads[k+2].color = sf::Color::Green;
        map_quads[k+3].position = sf::Vector2f(posx+i-50, posy+500);
        map_quads[k+3].color = sf::Color::Green;
        map_quads[k+4].position = sf::Vector2f(posx+i-50, posy);
        map_quads[k+4].color = sf::Color::Green;
        k+=5;
      }
      map_quads[k].position = sf::Vector2f(posx-50, posy);
      map_quads[k].color = sf::Color::Green;
      k+=1;
     for (size_t i=0; i!=500; i+=100){
        map_quads[k].position = sf::Vector2f(posx-50, posy+i+50);
        map_quads[k].color = sf::Color::Green;
        map_quads[k+1].position = sf::Vector2f(posx+450, posy+i+50);
        map_quads[k+1].color = sf::Color::Green;
        map_quads[k+2].position = sf::Vector2f(posx+450, posy+i+100);
        map_quads[k+2].color = sf::Color::Green;
        map_quads[k+3].position = sf::Vector2f(posx-50, posy+i+100);
        map_quads[k+3].color = sf::Color::Green;
        map_quads[k+4].position = sf::Vector2f(posx-50, posy+i+50);
        map_quads[k+4].color = sf::Color::Green;
        k+=5;
     }
     this->mapx=posx-50;
     this->mapy=posy;
}
void Map::add_ship(Ship ship, int posx, int posy){
   ship.set(mapx+(posx)*50+23,mapy+(posy)*50+23);
   ship.shipx=posx;
   ship.shipy=posy;
   if (!ship.vertical){
   for (int i=0; i<ship.parts; i++){
        field[posx][posy+i]= ship.index;
   }
       ships.push_back(new Ship(ship));
   }else  {
   for (int i=0; i<ship.parts; i++){
        field[posx+i][posy]= ship.index;
   }
       ships.push_back(new Ship(ship));
   }

}

int Map::shoot(int posx, int posy){
    if (posx>-1 and posy>-1 and posy<10 and posx<10) {
        if (field[posx][posy] == 0) {
            hits.push_back(Hit(false, mapx + (posx) * 50 + 18, mapy + (posy) * 50 + 18, posx, posy) );
            field[posx][posy] = 2;
            return 0;
        } else if (field[posx][posy] != 2 && field[posx][posy] != 0) {
            hits.push_back(Hit(true, mapx + (posx) * 50 + 18, mapy + (posy) * 50 + 18, posx, posy));
            for (auto i : ships) {
                if (i->index == field[posx][posy]) {
                    i->get_shot();
                    field[posx][posy] = 2;
                    if (i->health < 1) {
                        dead_ship(i->shipx, i->shipy, i->vertical, i->parts);
                        return i->index;
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const{
     states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

     // draw the vertex array
     target.draw(map_quads, states);
     if (!hidden){
       for (auto i:ships){
          target.draw(i->ship, states);
       }
     }
     for (Hit i: hits ){
       target.draw(i.hit, states);
     }
   }

std::vector<int> Map::capture_click(int x, int y){
  x-=mapx;
  y-=mapy;
  std::vector<int> res;
  if (x/50 < 10  and y/50 < 10 and x>0 and y>0){
     //std::cout<<"\nX "<<floor(x/50)<<" Y "<<floor(y/50);
     res.push_back(floor(x/50));
     res.push_back(floor(y/50));
     return res;
  }
  return res;
}

void Map::dead_ship(int x, int y, bool vertical, size_t parts){

    if (vertical){
        for(int i=x+parts; i>x-2; i--){
            shoot(i,y-1);
            shoot(i,y+1);
        }
        shoot(x-1,y);
        shoot(x+parts, y);
    }else{
       for(int i=y+parts; i>y-2; i--){
           shoot(x-1, i);
           shoot(x+1, i);
       }
       shoot(x, y-1);
       shoot(x, y+parts);
    }

}
int Map::get_field(int x, int y){
    if (x>-1 and y>-1 and y<10 and x<10){
        return field[x][y];
    }else{
        return -1;
    }
}

void Map::clean(){
    ships.clear();
    hits.clear();
    for (auto & i : field){
        for (int k=0; k<10; k++){
            i[k]=0;
        }
    }
}
void Map::set_ships(int seed){
  std::vector<int> ships_to_place={11, 12, 13, 14, 21, 22, 23, 31, 32};
  int x, y, v;
  y =std::rand()%5;
  x= std::rand()%5;
  v=std::rand()%2;
  add_ship(Ship(4, v, 41), x, y);
  dead_ship(x, y, v, 4);

  std::srand(seed);
  int trys =0;
  std::vector<int> pos(2);
  bool placed = false;
  std::vector<std::vector<int>> freespace;
  for (int j=0; j<10; j++){
        for (int p=0; p<10; p++){
            if (field[j][p]==0)
               freespace.push_back({j,p});
        }
  }
  while (trys<120 and !ships_to_place.empty()){
      pos=freespace[std::rand()%freespace.size()];
      //std::cout<<"\n x:"<<pos[0]<<" y:"<<pos[1]<<std::endl;
      if (std::rand()%2){
          for (int i = pos[1]; i <pos[1]+4 && !placed; i++) {
              if (get_field(pos[0], i)==0){
                  for (int  k=ships_to_place.size()-1; k>-1; k--){
                      if (ships_to_place[k]/10==(i-pos[1])){
                          std::cout<<"\nPLACED IND "<<ships_to_place[k]<<" SIZE:"<<ships_to_place.size()<<std::endl;
                          add_ship(Ship(ships_to_place[k]/10, false, ships_to_place[k]), pos[0], pos[1]);
                          dead_ship(pos[0], pos[1], false, ships_to_place[k]/10);
                          placed=true;
                          ships_to_place.erase(ships_to_place.begin()+k);
                          freespace.clear();
                          for (int j=0; j<10; j++){
                              std::cout<<"\n";
                              for (int p=0; p<10; p++){
                                  std::cout<<field[p][j]<<"  ";
                                  if (field[j][p]==0)
                                      freespace.push_back({j,p});
                              }
                          }
                          break;
                      }

                  }

              }else{
                  break;
              }
          }
      }if (!placed) {
          for (int i = pos[0]; i <pos[0]+4 && !placed;  i++) {
              if (get_field(i, pos[1])==0){
                  for (int  k=ships_to_place.size()-1; k>-1; k--){
                      if (ships_to_place[k]/10==i-pos[0]){
                          std::cout<<"\nPLACED IND "<<ships_to_place[k]<<" SIZE:"<<ships_to_place.size()<<std::endl;
                          add_ship(Ship(ships_to_place[k]/10, true, ships_to_place[k]), pos[0], pos[1]);
                          dead_ship(pos[0], pos[1], true, ships_to_place[k]/10);
                          placed=true;
                          ships_to_place.erase(ships_to_place.begin()+k);
                          freespace.clear();
                          for (int j=0; j<10; j++){
                              std::cout<<"\n";
                              for (int p=0; p<10; p++){
                                  std::cout<<field[p][j]<<"  ";
                                  if (field[j][p]==0)
                                      freespace.push_back({j,p});
                              }
                          }
                          break;
                      }

                  }
              }else{
                  break;
              }

              }

          }

      placed = false;
      trys+=1;
  }



  if (!ships_to_place.empty()){
      std::cout<<"\nUNABLE TO PLACE\n";
      /*for (int j=0; j<10; j++){
          std::cout<<"\n";
          for (int p=0; p<10; p++){
              std::cout<<field[p][j]<<"  ";
          }
      }*/
      clean();
      set_ships(seed+1);
  }else{
      for (auto & i : field){
          for (int k=0; k<10; k++){
              if (i[k] == 2)
                  i[k] = 0;
          }
  }
  hits.clear();
  std::cout<<"\nSEED "<<seed<<std::endl;  ///1622799351
}
}
