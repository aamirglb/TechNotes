#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

int main()
{
    sf::RenderWindow window(sf::VideoMode({1080, 720}), "Camera View");
    window.setFramerateLimit(4);

    sf::Texture texture;
    if(!texture.loadFromFile("crystal-32-blue.png")) {
        return -1;
    }
    // texture.setSmooth(true);

    auto wSize = window.getSize();
    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(wSize.x, wSize.y));
    // sf::View view(sf::FloatRect({0, 0}, {wSize.x, wSize.y}));
    // view.setCenter(sf::Vector2f(0, 150));
    window.setView(view);

    // Top Left
    sf::Vector2i spriteSize({32, 32});
    sf::Sprite sp1(texture);
    sp1.setOrigin({spriteSize.x * .5f, spriteSize.y * .5f});
    sp1.setPosition({-80, -80});
    sp1.setTextureRect(sf::IntRect({0, 0}, {spriteSize.x, spriteSize.y}));

    // Top right
    sf::Sprite sp2(texture);
    sp2.setOrigin({spriteSize.x * .5f, spriteSize.y * .5f});
    sp2.setPosition({80, -80});
    sp2.setTextureRect(sf::IntRect({0, 0}, {spriteSize.x, spriteSize.y}));

    // Bottom right
    sf::Sprite sp3(texture);
    sp3.setOrigin({spriteSize.x * .5f, spriteSize.y * .5f});
    sp3.setPosition({80, 80});
    sp3.setTextureRect(sf::IntRect({0, 0}, {spriteSize.x, spriteSize.y}));

    // Bottom left
    sf::Sprite sp4(texture);
    sp4.setOrigin({spriteSize.x * .5f, spriteSize.y * .5f});
    sp4.setPosition({-80, 80});
    sp4.setTextureRect(sf::IntRect({0, 0}, {spriteSize.x, spriteSize.y}));

    view.setViewport(sf::FloatRect({0, 0}, {.5f, .5f}));

    // view.setSize({wSize.x, wSize.y * 2});
    // view.setRotation(sf::degrees(45.f));
    window.setView(view);

    std::vector<sf::View> views {
        sf::View(sf::FloatRect({0, 0}, {.5f, .5f})),
        sf::View(sf::FloatRect({.5f, 0}, {.5f, .5f})),
        sf::View(sf::FloatRect({0, .5f}, {.5f, .5f})),
        sf::View(sf::FloatRect({.5f, .5f}, {.5f, .5f})),
    };

    while(window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            window.close();

        if(event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2f sceneCoords = window.mapPixelToCoords(
                sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
            std::cout << "(" << sceneCoords.x << ", " << sceneCoords.y << ")" << std::endl;
        }
        window.clear(sf::Color::Black);
        // for(const auto &v : views) {
            // window.setView(views[0]);
            window.draw(sp1);
            window.draw(sp2);
            window.draw(sp3);
            window.draw(sp4);
        // }
        window.display();
    }
}