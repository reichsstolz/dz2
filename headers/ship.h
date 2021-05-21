// кораблики
#ifndef SHIP_H
#define SHIP_H
#include <SFML/Graphics.hpp>
#include <string>
class Ship : public sf::Drawable, public sf::Transformable{

public:
  size_t shipx;
  size_t shipy;
  size_t parts;
  bool set(int posx, int posy);
  //void get_shot(string part)
  bool vertical;
  Ship(size_t p, bool v) : parts{p}, vecrtical{v} {}
  //sf::VertexArray ship_vertex;
  sf::ConvexShape ship;

private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


};
#endif
