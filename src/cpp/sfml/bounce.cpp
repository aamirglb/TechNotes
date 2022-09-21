#include <SFML/Graphics.hpp>
#include <iostream>

int main(){
    sf::RenderWindow window(sf::VideoMode({1000, 700}), "project");
    window.setFramerateLimit(30);

    sf::RectangleShape rect;

    int w = 100;
    int h = 100;
    rect.setSize(sf::Vector2f(w, h));

    sf::Vector2f rectangle_position(500 - (w/2), 300 - (h/2));
    rect.setPosition(rectangle_position);

    sf::Vector2f velocity(0, 6);

   while (window.isOpen()) {
           sf::Event event;
           while (window.pollEvent(event)) {
               if (event.type == sf::Event::Closed) window.close();
               if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
           }
           rectangle_position.y += velocity.y;

            if (rectangle_position.x > 1000 - w) {
            //    x_velocity = x_velocity * -1;
           }

           if (rectangle_position.x < 1 ) {
            //    x_velocity = x_velocity * -1;
           }

           if ((rectangle_position.y) > 700 - h) {
            rectangle_position.y -= 3;
            velocity.y *= -0.7f;
           }

           if (rectangle_position.y < 50) {
            velocity.y *= -0.7f;
           }

           rect.setPosition(rectangle_position);


           window.clear();
           window.draw(rect);

           window.display();
    }

}