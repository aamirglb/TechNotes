#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
    sf::CircleShape shape(50.f);
    // shape.setFillColor(sf::Color::Green);
    shape.setFillColor(sf::Color(100, 250, 50));
    shape.setPosition(10, 10);
    shape.setPointCount(200);

    sf::CircleShape shape2(50.f);
    shape2.setFillColor(sf::Color(150, 50, 250));
    shape2.setOutlineThickness(-10.f);
    shape2.setOutlineColor(sf::Color(250, 150, 100));
    shape2.setPosition(120, 10);

    sf::CircleShape shape3(50.f);
    shape3.setFillColor(sf::Color::Transparent);
    shape3.setOutlineThickness(2.f);
    shape3.setOutlineColor(sf::Color::White);
    shape3.setPosition(230, 10);

    sf::RectangleShape rect(sf::Vector2f(120.f, 50.f));
    rect.setFillColor(sf::Color::Magenta);
    rect.setPosition(10, 120);

    sf::CircleShape triangle(80.f, 3);
    triangle.setPosition(140, 120);
    triangle.setFillColor(sf::Color::Blue);

    sf::CircleShape square(80.f, 4);
    square.setPosition(310, 120);
    square.setOrigin(40, 40);
    square.setFillColor(sf::Color::Red);

    sf::CircleShape octagon(80.f, 8);
    octagon.setPosition(10, 120+160+10);
    octagon.setFillColor(sf::Color::Cyan);

    window.setFramerateLimit(5);
    float angle = 0;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        angle += 1;
        if(angle > 359.) angle = 0;
        square.rotate(angle);
        window.clear();
        window.draw(shape);
        window.draw(shape2);
        window.draw(shape3);
        window.draw(rect);
        window.draw(triangle);
        window.draw(square);
        window.draw(octagon);
        window.display();
    }

    return 0;
}
