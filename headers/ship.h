// кораблики
#ifndef SHIP_H
#define SHIP_H
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
class Ship : public sf::Drawable, public sf::Transformable{

public:
  size_t shipx, shipy;
  int parts;
  int health;
  int index;
  bool set(int posx, int posy);
  void get_shot();
  bool vertical;
  Ship(int p, bool v, int ind) : parts{p}, vertical{v}, health{p}, index{ind} {}
  //sf::VertexArray ship_vertex;
  sf::ConvexShape ship;

private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


};
#endif
