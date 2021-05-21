#ifndef MAP_H
#define MAP_H
#include <SFML/Graphics.hpp>
#include "ship.h"
#include <vector>
class Map : public sf::Drawable, public sf::Transformable{

public:
  size_t mapx;
  size_t mapy;
  bool hidden;
  bool game_over;
  std::vector<Ship> ships;
  std::vector<std::vector<int>> field;
  
  void add_ship(Ship ship, int posx, int posy);
  void shoot(int posx, int posy);
  bool set(int posx, int posy);

private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  sf::VertexArray map_quads;
};
#endif
