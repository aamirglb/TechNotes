#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <vector>

uint32_t winWidth {1080}, winHeight{840};

int main()
{
    sf::RenderWindow window(sf::VideoMode({winWidth, winHeight}), "Random circles");
    // window.setFramerateLimit(10);

    // for generating random height
    std::random_device d;
    std::default_random_engine engine(d());
    std::uniform_int_distribution<int32_t> dim(5, 20);
    std::uniform_int_distribution<int32_t> col(0, 255);
    std::uniform_int_distribution<int32_t> pos(0, 1080);

    sf::CircleShape *circle;
    std::vector<sf::CircleShape *> circles;

    while(window.isOpen()) {
        auto start(std::chrono::high_resolution_clock::now());
        sf::Event event;

        while(window.pollEvent(event)) {
            if(event.type == sf::Event::EventType::Closed)
                window.close();
            else if(event.type == sf::Event::EventType::KeyReleased) {
                if(event.key.code == sf::Keyboard::Key::Escape)
                    window.close();
            }
        }

        int32_t r = col(engine);
        int32_t g = col(engine);
        int32_t b = col(engine);
        int32_t a = col(engine);

        float x = pos(engine);
        float y = pos(engine);

        int32_t radius = dim(engine);

        window.clear(sf::Color::White);
        circle = new sf::CircleShape;
        circle->setFillColor(sf::Color(r, g, b, a));
        circle->setRadius(radius);
        circle->setPosition({x, y});

        circles.push_back(circle);

        for(auto c : circles)
            window.draw(*c);

        window.display();

        auto end(std::chrono::high_resolution_clock::now());
        auto elapsedTime(end - start);
        float frameTime{std::chrono::duration_cast<
            std::chrono::duration<float, std::milli>>(elapsedTime).count()};

        auto ftSeconds(frameTime / 100.f);
        auto fps(1.f/ ftSeconds);

        window.setTitle("Random Circles: "
                        + std::to_string(circles.size())
                        + "        FT: "
                        + std::to_string(frameTime)
                        + "       FPS: " + std::to_string(fps));
    }
}