#include "headers/map.h"
// compile g++ map.cpp test.cpp headers/map.h -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
void Map::set(int posx, int posy){
      for (int i=0; i<10; i++){
          field[i]= new int[10];
          for (int k=0; k<10; k++){
              field[i][k]=0;
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

void Map::shoot(int posx, int posy){
  std::cout<<"\nSHOOTING  "<<posx<<" "<<posy<<"\n";
    if (posx>-1 and posy>-1 and posy<10 and posx<10) {
        /*for (int i=0; i<10; i++){
            std::cout<<"\n";
            for (int k=0; k<10; k++){
                std::cout<<field[i][k]<<" ";
            }
        }*/
        std::cout<<"\nSHOOTING V  "<<posx<<" "<<posy<<"\n";
        if (field[posx][posy] == 0) {
            hits.push_back(Hit(false, mapx + (posx) * 50 + 18, mapy + (posy) * 50 + 18, posx, posy) );
            field[posx][posy] = 2;
        } else if (field[posx][posy] != 2 && field[posx][posy] != 0) {
            hits.push_back(Hit(true, mapx + (posx) * 50 + 18, mapy + (posy) * 50 + 18, posx, posy));
            for (auto i : ships) {
                if (i->index == field[posx][posy]) {
                    i->get_shot();

                    if (i->health < 1) {
                        dead_ship(i->shipx, i->shipy, i->vertical, i->parts);
                    }
                    //delete field[posx][posy];
                    field[posx][posy] = 2;
                }
            }
        }
    }
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
     std::cout<<"\nX "<<floor(x/50)<<" Y "<<floor(y/50);
     res.push_back(floor(x/50));
     res.push_back(floor(y/50));
     return res;
  }
  return res;
}

void Map::dead_ship(int x, int y, bool vertical, size_t parts){

    if (vertical){
        //std::cout<<"\n V\n";
        //std::cout<<"\nDead_ship:  i="<<x-1<<"  i<"<<x+parts+1<<" x "<<y-1<<" "<<y+1<<" \n";
        for(int i=x+parts; i>x-2; i--){
            shoot(i,y-1);
            shoot(i,y+1);
        }
        shoot(x-1,y);
        shoot(x+parts, y);
    }else{
       //std::cout<<std::endl<<"G"<<std::endl;
       //std::cout<<std::endl<<"Dead_ship:  i ="<<y-1<<"  i< "<<y+parts+1<<" x "<<x-1<<" "<<x+1<<std::endl;
       for(int i=y+parts; i>y-2; i--){
           //std::cout<<std::endl<<"AAAAAAAAAAAAAAAAAA"<<std::endl;
           shoot(x-1, i);
           shoot(x+1, i);
       }
       shoot(x, y-1);
       shoot(x, y+parts);
    }

}

/*void Map::set_ships(){
  std::vector<int> avalible_ships={1, 1, 1, 1, 2, 2, 2, 3, 3, 4};
  std::srand(std::time(nullptr));
  int x, y;
  for (int i=0; i<4;  i++){
    x = std::rand()%10;
    y = std::rand()%10;
    field[x][y] =new int(1);

  }
}*/
