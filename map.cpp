#include "headers/map.h"
// compile g++ map.cpp test.cpp headers/map.h -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
bool Map::set(int posx, int posy){
      field.resize(10);
      for (std::vector<int> i : field){
            i.resize(10, 0);
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
     this->mapx=posx;
     this->mapy=posy;
     return true;
}
void Map::add_ship(Ship ship, int posx, int posy){
   ship.set(mapx+(posx-1)*50+23,mapy+(posy)*50+23);
   ship.shipx=posx;
   ship.shipy=posy;
   for (int i=0; i<ship.parts && ship.vertical; i++)
        field[posx][posy +i]=1;
   for (int i=0; i<ship.parts && !ship.vertical; i++)
        field[posx+i][posy]=1;
   ships.push_back(ship);
}

void Map::shoot(int posx, int posy){

}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const{
     states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

     // draw the vertex array
     target.draw(map_quads, states);
     if (!hidden){
       for (Ship i:ships){
          target.draw(i.ship, states);
       }
     }
}
