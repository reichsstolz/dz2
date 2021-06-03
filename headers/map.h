#ifndef MAP_H
#define MAP_H
#include <SFML/Graphics.hpp>
#include "ship.h"
#include "hit.h"
#include <vector>
#include <cmath>
#include <iostream>
class Map : public sf::Drawable, public sf::Transformable{

public:
  size_t mapx;
  size_t mapy;
  bool hidden;
  std::vector<Ship*> ships;
  int* field[10];
  std::vector<Hit> hits;
  void add_ship(Ship ship, int posx, int posy);
  int shoot(int posx, int posy);
  void set(int posx, int posy);
  //void set_ships();
  void dead_ship(int x, int y, bool vertical, size_t parts);
  std::vector<int> capture_click(int y , int x);
private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  sf::VertexArray map_quads;
};

#endif
