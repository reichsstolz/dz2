// попадание и молоко
#ifndef HIT_H
#define HIT_H
#include <SFML/Graphics.hpp>
#include <string>
class Hit : public sf::Drawable, public sf::Transformable{

public:
  size_t hitx;
  size_t hity;
  bool set(int posx, int posy);
  //void get_shot(string part)
  bool hit_ship;
  Hit(bool h) : hit_ship{h} {}
  sf::CircleShape hit;

private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


};
#endif
