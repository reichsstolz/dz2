#include "headers/ship.h"

bool Ship::set(int posx, int posy){

  if (parts!=1) {
      ship.setPointCount(6);
      if (vertical) {
          ship.setPoint(0, sf::Vector2f(posx, posy));
          ship.setPoint(1, sf::Vector2f(posx + 14, posy - 8));
          ship.setPoint(2, sf::Vector2f(posx + 50 * (parts - 1), posy - 8));
          ship.setPoint(3, sf::Vector2f(posx + 14 + 50 * (parts - 1), posy));
          ship.setPoint(4, sf::Vector2f(posx + 50 * (parts - 1), posy + 8));
          ship.setPoint(5, sf::Vector2f(posx + 14, posy + 8));
          ship.setFillColor(sf::Color(150, 50, 250));
      } else {
          ship.setPoint(0, sf::Vector2f(posx, posy));
          ship.setPoint(1, sf::Vector2f(posx - 8, posy + 14));
          ship.setPoint(2, sf::Vector2f(posx - 8, posy + 50 * (parts - 1)));
          ship.setPoint(3, sf::Vector2f(posx, posy + 14 + 50 * (parts - 1)));
          ship.setPoint(4, sf::Vector2f(posx + 8, posy + 50 * (parts - 1)));
          ship.setPoint(5, sf::Vector2f(posx + 8, posy + 14));
          ship.setFillColor(sf::Color(150, 50, 250));
      }
  }else{
      ship.setPointCount(4);
      ship.setPoint(0, sf::Vector2f(posx-7, posy-7));
      ship.setPoint(1, sf::Vector2f(posx-7, posy+8));
      ship.setPoint(2, sf::Vector2f(posx+8, posy+8));
      ship.setPoint(3, sf::Vector2f(posx+8, posy-7));
      ship.setFillColor(sf::Color(150, 50, 250));
  }
  return true;
}
void Ship::get_shot() {
    health-=1;
    std::cout<<"\nIndex: "<<index<<" Health: "<<health<<"\n";
}
void Ship::draw(sf::RenderTarget& target, sf::RenderStates states) const{
     states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

     // draw the vertex array
     target.draw(ship, states);
}
