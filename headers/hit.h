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
  Hit(bool h, int x, int y);
  sf::CircleShape hit;

private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


};

//int* capture_hit(int x, int y);
#endif
