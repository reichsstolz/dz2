#include "headers/map.h"
#include "headers/ship.h"
#include "headers/hit.h"
#include "headers/player.h"
int main()
{
   sf::RenderWindow window(sf::VideoMode(1050, 600), "My window");

   Player player(false);
   Player enemy(true);
   player.map.hidden= false;
   enemy.map.hidden= false;
   player.map.set(10, 40);
   enemy.map.set(540, 40);
   while (window.isOpen())
   {
       // check all the window's events that were triggered since the last iteration of the loop
       sf::Event event;
       while (window.pollEvent(event))
       {
           // "close requested" event: we close the window
           if (event.type == sf::Event::Closed)
               window.close();

           if (event.type == sf::Event::MouseButtonPressed){
               if (event.mouseButton.button == sf::Mouse::Left){
                   if (!player.ships_set){
                       player.set_ships(event.mouseButton.x, event.mouseButton.y);
                   }else{
                       player.get_hit(event.mouseButton.x, event.mouseButton.y);
                   }
                 /*if (map.capture_click(event.mouseButton.x, event.mouseButton.y)){
                   std::cout<<"\n$HIT$\n";
                   std::cout<<event.mouseButton.x<<" "<<event.mouseButton.y;
                 }*/
               }
           }
       }

       // clear the window with black color
       window.clear(sf::Color::Black);

       // draw everything here...
       // window.draw(...);
       window.clear();
       window.draw(player.map);
       window.draw(enemy.map);
       //window.draw(hit);
       //window.draw(hit1);
       window.display();
   }

   return 0;
}
