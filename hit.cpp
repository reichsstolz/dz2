#include "headers/hit.h"

bool Hit::set(int posx, int posy){
   hit.setRadius(5.f);
   hit.setPosition(posx, posy);
   if (hit_ship){
     hit.setFillColor(sf::Color(150, 0, 0));
   }else{
     hit.setFillColor(sf::Color(255, 255, 255));
   }
   return true;
 }
Hit::Hit(bool h, int x, int y, size_t hx, size_t hy) : hit_ship{h}
{
  set(x, y);
  hitx=hx;
  hity=hy;
}
void Hit::draw(sf::RenderTarget& target, sf::RenderStates states) const{
       states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

       // draw the vertex array
       target.draw(hit, states);
  }
