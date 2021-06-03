#include "headers/map.h"
#include "headers/ship.h"
#include "headers/hit.h"
#include "headers/player.h"
int main()
{
   sf::RenderWindow window(sf::VideoMode(1050, 600), "Sausages Party");
    sf::Text text;
    //sf:: Font font;
    //font.loadFromFile("arial.ttf");
    //text.setString("YOU LOST");
    //text.setFont(font);





   /*
   text.setCharacterSize(50); // in pixels, not points!
   text.setPosition(290, 500);
   text.setFillColor(sf::Color::Green);
   text.setStyle(sf::Text::Bold);*/

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
               if (event.mouseButton.button == sf::Mouse::Left and !player.game_over){
                   if (player.game_over){
                       //window.draw(text);
                       std::cout<<"\nLost player\n";
                   }
                   if (enemy.game_over){
                       //window.draw(text);
                       std::cout<<"\nLost enemy\n";
                   }
                   if (!player.ships_set or !enemy.ships_set){
                       player.set_ships(event.mouseButton.x, event.mouseButton.y);
                       enemy.set_ships(event.mouseButton.x, event.mouseButton.y);
                   }else{
                      enemy.set_priority(player.get_hit(enemy.shoot()));
                      enemy.get_hit(enemy.map.capture_click(event.mouseButton.x, event.mouseButton.y));

                   }
               }
           }
       }

       // clear the window with black color
       window.clear(sf::Color::Black);
       window.clear();

       window.draw(player.map);
       window.draw(enemy.map);
       window.display();
   }

   return 0;
}
