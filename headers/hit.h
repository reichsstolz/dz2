// попадание и молоко
#ifndef HIT_H
#define HIT_H
#include <SFML/Graphics.hpp>
#include <string>
class Hit : public sf::Drawable, public sf::Transformable{

public:
  int hitx;
  int hity;
  bool set(int posx, int posy);
  bool hit_ship;
  Hit(bool h, int x, int y, size_t hx, size_t hy);
  sf::CircleShape hit;

private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


};

//int* capture_hit(int x, int y);
#endif
