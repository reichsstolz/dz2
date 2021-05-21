#include "headers/ship.h"

bool Ship::set(int posx, int posy){
  //ship_vertex.resize(7);
  //ship_vertex.setPrimitiveType(sf::LineStrip);
  ship.setPointCount(6);
  if (vertical){
    ship.setPoint(0, sf::Vector2f(posx, posy));
    ship.setPoint(1, sf::Vector2f(posx+14, posy-8));
    ship.setPoint(2, sf::Vector2f(posx+50*(parts-1), posy-8));
    ship.setPoint(3, sf::Vector2f(posx+14+50*(parts-1), posy));
    ship.setPoint(4, sf::Vector2f(posx+50*(parts-1), posy+8));
    ship.setPoint(5, sf::Vector2f(posx+14, posy+8));
    ship.setFillColor(sf::Color(150, 50, 250));
    /*ship_vertex[0].position = sf::Vector2f(posx, posy);
    ship_vertex[0].color = sf::Color::Blue;
    ship_vertex[1].position = sf::Vector2f(posx+14, posy-8);
    ship_vertex[1].color = sf::Color::Blue;
    ship_vertex[2].position = sf::Vector2f(posx+50*(parts-1), posy-8);
    ship_vertex[2].color = sf::Color::Blue;
    ship_vertex[3].position = sf::Vector2f(posx+14+50*(parts-1), posy);
    ship_vertex[3].color = sf::Color::Blue;
    ship_vertex[4].position = sf::Vector2f(posx+50*(parts-1), posy+8);
    ship_vertex[4].color = sf::Color::Blue;
    ship_vertex[5].position = sf::Vector2f(posx+14, posy+8);
    ship_vertex[5].color = sf::Color::Blue;
    ship_vertex[6].position = sf::Vector2f(posx, posy);
    ship_vertex[6].color = sf::Color::Blue;*/
  }else{
    ship.setPoint(0, sf::Vector2f(posx, posy));
    ship.setPoint(1, sf::Vector2f(posx-8, posy+14));
    ship.setPoint(2, sf::Vector2f(posx-8, posy+50*(parts-1)));
    ship.setPoint(3, sf::Vector2f(posx, posy+14+50*(parts-1)));
    ship.setPoint(4, sf::Vector2f(posx+8, posy+50*(parts-1)));
    ship.setPoint(5, sf::Vector2f(posx+8, posy+14));
    ship.setFillColor(sf::Color(150, 50, 250));
    /*ship_vertex[0].position = sf::Vector2f(posx, posy);
    ship_vertex[0].color = sf::Color::Blue;
    ship_vertex[1].position = sf::Vector2f(posx-8, posy+14);
    ship_vertex[1].color = sf::Color::Blue;
    ship_vertex[2].position = sf::Vector2f(posx-8, posy+50*(parts-1));
    ship_vertex[2].color = sf::Color::Blue;
    ship_vertex[3].position = sf::Vector2f(posx, posy+14+50*(parts-1));
    ship_vertex[3].color = sf::Color::Blue;
    ship_vertex[4].position = sf::Vector2f(posx+8, posy+50*(parts-1));
    ship_vertex[4].color = sf::Color::Blue;
    ship_vertex[5].position = sf::Vector2f(posx+8, posy+14);
    ship_vertex[5].color = sf::Color::Blue;
    ship_vertex[6].position = sf::Vector2f(posx, posy);
    ship_vertex[6].color = sf::Color::Blue;*/
  }
  return true;
}

void Ship::draw(sf::RenderTarget& target, sf::RenderStates states) const{
     states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

     // draw the vertex array
     target.draw(ship, states);
}
