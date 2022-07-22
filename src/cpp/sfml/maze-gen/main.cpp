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
    uint32_t winWidth = std::stoi(appSettings.getValue("winWidth")) + 4;    // add some offset
    uint32_t winHeight = std::stoi(appSettings.getValue("winHeight")) + 4;  // add some offset
    uint32_t cellWidth = std::stoi(appSettings.getValue("cellWidth"));
    bool   pause { false };
    bool   fill { true };

    sf::RenderWindow window(sf::VideoMode({winWidth, winHeight}), "Maze Generator");
    // window.setFramerateLimit(1);

    // create maze class
    auto maze = std::make_unique<Maze>(window, appSettings);

    while(window.isOpen()) {
        auto start(std::chrono::high_resolution_clock::now());

        sf::Event e;

        while(window.pollEvent(e)) {
            if(e.type == sf::Event::EventType::Closed)
                window.close();
            else if(e.type == sf::Event::EventType::KeyReleased) {
                switch(e.key.code) {
                    case sf::Keyboard::Key::Escape:
                        window.close();
                        break;
                    case sf::Keyboard::Key::Space:
                        maze->reset();
                        break;
                    // pause
                    case sf::Keyboard::Key::P:
                        pause = true;
                        break;
                    // restart
                    case sf::Keyboard::Key::R:
                        pause = false;
                        break;
                    // toggle grid fill
                    case sf::Keyboard::Key::F:
                        fill = !fill;
                        maze->setFill(fill);
                        maze->showTracer(fill);
                        break;
                }
            }
        }

        if(!pause) {
            window.clear(sf::Color::Black);
            maze->update();
            maze->draw();
            window.display();
        }

        auto end(std::chrono::high_resolution_clock::now());
        auto elapsedTime(end - start);
        FrameTime ft{std::chrono::duration_cast<
            std::chrono::duration<float, std::milli>>(elapsedTime).count()};

        auto ftSeconds(ft / 100.f);
        auto fps(1.f/ ftSeconds);

        window.setTitle("Maze Generator          Visited: "
                        + maze->getStats()
                        + "        FT: "
                        + std::to_string(ft)
                        + "       FPS: " + std::to_string(fps));
    }
}