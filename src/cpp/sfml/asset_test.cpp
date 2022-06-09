#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode({640, 480}), "Asset Manager");
    window.setFramerateLimit(60);
    AssetManager manager;

    sf::Sprite sprite1 = sf::Sprite(AssetManager::GetTexture("green-leaf.png"));
    sf::Sprite sprite2 = sf::Sprite(AssetManager::GetTexture("tile.png"));
    sprite2.move({200, 0});

    try {
        sf::Sprite sprite3 = sf::Sprite(AssetManager::GetTexture("test.png"));
    } catch(std::invalid_argument e) {
        std::cerr << e.what() << std::endl;
    } catch(std::exception e) {
        std::cerr << e.what() << std::endl;
    }

    while(window.isOpen()) {
        sf::Event event;

        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            window.close();

        window.clear(sf::Color::Black);
        window.draw(sprite1);
        window.draw(sprite2);
        window.display();
    }
}