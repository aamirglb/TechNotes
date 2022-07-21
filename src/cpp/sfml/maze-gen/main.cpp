#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <chrono>

#include "settings.hpp"
#include "cell.hpp"
#include "maze.hpp"

using FrameTime = float;

int main()
{
    // Read application settings
    Settings appSettings("settings.ini");
    uint32_t winWidth = std::stoi(appSettings.getValue("winWidth")) + 4;
    uint32_t winHeight = std::stoi(appSettings.getValue("winHeight")) + 4;
    uint32_t cellWidth = std::stoi(appSettings.getValue("cellWidth"));

    sf::RenderWindow window(sf::VideoMode({winWidth, winHeight}), "Maze Generator");
    // window.setFramerateLimit(1);

    Maze maze(window, appSettings);

    while(window.isOpen()) {
        auto start(std::chrono::high_resolution_clock::now());

        sf::Event e;

        while(window.pollEvent(e)) {
            if(e.type == sf::Event::EventType::Closed)
                window.close();
            else if(e.type == sf::Event::EventType::KeyReleased &&
                    e.key.code == sf::Keyboard::Key::Escape) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        maze.update();
        maze.draw();
        window.display();

        auto end(std::chrono::high_resolution_clock::now());
        auto elapsedTime(end - start);
        FrameTime ft{std::chrono::duration_cast<
            std::chrono::duration<float, std::milli>>(elapsedTime).count()};

        auto ftSeconds(ft / 100.f);
        auto fps(1.f/ ftSeconds);

        window.setTitle("FT: " + std::to_string(ft) + "       FPS: " + std::to_string(fps));
    }
}