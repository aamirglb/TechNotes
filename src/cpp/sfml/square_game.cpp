#include <SFML/Graphics.hpp>
#include <iostream>

void initShape(sf::RectangleShape& shape,
                const sf::Vector2f &pos,
                const sf::Color &color)
{
    shape.setFillColor(color);
    shape.setPosition(pos);
    shape.setOrigin(shape.getSize() * 0.5f);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({480, 180}), "Square Game");
    window.setFramerateLimit(60);

    sf::Vector2f startPos = sf::Vector2f(50, 50);
    sf::RectangleShape playerRect(sf::Vector2f(50, 50));

    initShape(playerRect, startPos, sf::Color::Green);

    sf::RectangleShape targetRect(sf::Vector2f(50, 50));
    initShape(targetRect, sf::Vector2f(400, 50), sf::Color::Blue);

    sf::RectangleShape badRect(sf::Vector2f(50, 50));
    initShape(badRect, sf::Vector2f(250, 50), sf::Color::Red);

    while(window.isOpen()) {
        sf::Event event;

        while(window.pollEvent(event)) {
            if(event.type == sf::Event::EventType::Closed)
                window.close();
        }

        playerRect.move({1, 0});

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            window.close();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
            playerRect.move({0, 1});
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
            playerRect.move({0, -1});

        if((playerRect.getPosition().x + (playerRect.getSize().x / 2.0f)) > 480)
            playerRect.setPosition(startPos);

        if(playerRect.getGlobalBounds().findIntersection(targetRect.getGlobalBounds())) {
            std::cout << "hit target" << std::endl;
            window.close();
        }

        if(playerRect.getGlobalBounds().findIntersection(badRect.getGlobalBounds())) {
            std::cout << "hit red rectangle" << std::endl;
            playerRect.setPosition(startPos);
        }


        window.clear(sf::Color::Black);
        window.draw(playerRect);
        window.draw(targetRect);
        window.draw(badRect);
        window.display();
    }
}