#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

constexpr uint32_t width {240};
constexpr uint32_t height {240};
constexpr int32_t maxIterations {50};

int32_t map(int32_t x, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int main() {
    // Create window
    sf::RenderWindow window(sf::VideoMode({width, height}), "Mandelbroth");
    window.setFramerateLimit(30);

    std::vector<sf::Vertex> points(width * height);

    for(uint32_t i {}; i < width; ++i) {
        for(uint32_t j {}; j < height; ++j) {
            points[i*width+j].position = sf::Vector2f(i, j);
            points[i*width+j].color = sf::Color::Black;
        }
    }

    for(int32_t i {}; i < width; ++i) {
        for(int32_t j {}; j < height; ++j) {
            int32_t a = i;
            int32_t b = j;

            int32_t n {};
            int32_t ca = a;
            int32_t cb = b;

            while(n < maxIterations) {
                int32_t aa = a*a - b*b;
                int32_t bb = 2 * a * b;
                a = aa + ca;
                b = bb + cb;

                if(abs(a+b) > 16) break;
                ++n;
            }
            uint8_t bright {255};
            bright = map(n, 0, maxIterations, 0, 255);

            if(n == maxIterations) bright = 0;
            points[i*width+j].color = sf::Color::Color(bright, bright, bright);

        }
    }
    while(window.isOpen()) {
        sf::Event e;

        while (window.pollEvent(e)) {
            if(e.type == sf::Event::EventType::Closed) {
                window.close();
            } else if(e.type == sf::Event::EventType::KeyReleased &&
                      e.key.code == sf::Keyboard::Key::Escape) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        for(const auto& point : points) {
            window.draw(&point, 1, sf::Points);
        }


        window.display();
    }
}