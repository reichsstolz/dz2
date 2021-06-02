#include "headers/map.h"
#include "headers/ship.h"
#include "headers/hit.h"
int main()
{
   // create the window
   sf::RenderWindow window(sf::VideoMode(800, 800), "My window");
   Map mymap;
   mymap.hidden=false;
   mymap.set(80,80);
   Ship ship(3, true);
   Ship ship1(4, false);
   mymap.add_ship(ship, 2, 2);
   mymap.add_ship(ship1, 5, 4);
   //map.shoot(2,2);
   //map.shoot(3,3);
   // run the program as long as the window is open
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
                 //std::cout<<event.mouseButton.x<<" "<<event.mouseButton.y<<"\n";
                 if (map.capture_click(event.mouseButton.x, event.mouseButton.y)){
                   std::cout<<"\n$HIT$\n";
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
