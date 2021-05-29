#include "headers/map.h"
#include "headers/ship.h"
#include "headers/hit.h"
int main()
{
   // create the window
   sf::RenderWindow window(sf::VideoMode(800, 800), "My window");
   Map map;
   map.hidden=false;
   map.set(80,80);
   Ship ship(3, true, 33);
   Ship ship1(4, false, 41);
   Ship ship2(3, false, 35);
   map.add_ship(ship2, 9, 3);
   map.add_ship(ship, 2, 2);
   map.add_ship(ship1, 5, 4);
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

                 if (map.capture_click(event.mouseButton.x, event.mouseButton.y)){
                   std::cout<<"\n$HIT$\n";
                     std::cout<<event.mouseButton.x<<" "<<event.mouseButton.y;
                 }
               }
           }
       }

       // clear the window with black color
       window.clear(sf::Color::Black);

       // draw everything here...
       // window.draw(...);
       window.clear();
       window.draw(map);
       //window.draw(hit);
       //window.draw(hit1);
       window.display();
   }

   return 0;
}
