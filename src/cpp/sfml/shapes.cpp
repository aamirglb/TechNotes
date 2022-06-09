#include <SFML/Graphics.hpp>
#include <iostream>

uint32_t winWidth {1080}, winHeight{840};

enum class Movements {
    eRIGHT,
    eDOWN,
    eLEFT,
    eUP,
};

int main()
{
    sf::RenderWindow window(sf::VideoMode({winWidth, winHeight}), "Shapes");
    window.setFramerateLimit(60);

    sf::CircleShape circle(50);
    circle.setFillColor(sf::Color::Red);
    circle.setOutlineColor(sf::Color::White);
    circle.setOutlineThickness(1);

    sf::RectangleShape rect(sf::Vector2f(50, 50));
    rect.setFillColor(sf::Color::Green);
    rect.setPosition(sf::Vector2f(50, 50));
    rect.setOrigin(sf::Vector2f(25, 25));

    sf::ConvexShape triangle;
    triangle.setPointCount(3);
    triangle.setPoint(0, sf::Vector2f(200, 200));
    triangle.setPoint(1, sf::Vector2f(300, 300));
    triangle.setPoint(2, sf::Vector2f(200, 300));
    triangle.setFillColor(sf::Color::Blue);

    Movements movement {Movements::eRIGHT};
    sf::Vector2f velocity{1, 0};
    sf::Angle   rotation{sf::degrees(1.5f)};

    while(window.isOpen()) {
        sf::Event event;

        while(window.pollEvent(event)) {
            if(event.type == sf::Event::EventType::Closed)
                window.close();
            else if(event.type == sf::Event::EventType::KeyReleased) {
                if(event.key.code == sf::Keyboard::Key::Escape)
                    window.close();
            }
        }

        switch(movement) {
        case Movements::eRIGHT:
            if((rect.getPosition().x + 25) > winWidth - 20)
                movement = Movements::eDOWN;
            velocity = {1, 0};
            rotation = sf::degrees(1.5f);
            break;
        case Movements::eDOWN:
            if((rect.getPosition().y + 25) > winHeight - 20)
                movement = Movements::eLEFT;
            velocity = {0, 1};
            rotation = sf::degrees(1.5f);
            break;
        case Movements::eLEFT:
            if((rect.getPosition().x - 25) < 20)
                movement = Movements::eUP;
            velocity = {-1, 0};
            rotation = sf::degrees(-1.5f);
            break;
        case Movements::eUP:
            if((rect.getPosition().y - 25) < 20)
                movement = Movements::eRIGHT;
            velocity = {0, -1};
            rotation = sf::degrees(-1.5f);
            break;
        }
        rect.move(velocity);
        rect.rotate(rotation);

        window.clear(sf::Color::Black);
        window.draw(circle);
        window.draw(rect);
        window.draw(triangle);
        window.display();
    }
}