#include <sfml/Graphics.hpp>
#include <vector>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode({640, 480}), "Texture");
    window.setFramerateLimit(60);

    sf::RenderTexture rt;
    rt.create({32, 32}/*, false*/);

    std::vector<sf::Color> colors {
        sf::Color::Red,
        sf::Color::White,
        sf::Color::Cyan,
        sf::Color::Blue,
        sf::Color::Yellow,
    };
    int32_t max_colors = colors.size();
    int32_t frame{};

    sf::Sprite sp(rt.getTexture());
    sp.setOrigin({16, 16});
    sp.move({640/2., 480/2.});

    while(window.isOpen()) {
        sf::Event event;
        ++frame;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) window.close();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                window.close();
        }

        int32_t r = (frame & 0xFF0000) >> 16;
        int32_t g = (frame & 0x00FF00) >> 8;
        int32_t b = (frame & 0x0000FF);

        if(frame % 30 == 0)
            std::cout << "(" << r << ", " << g << ", " << b << ")\n";

        sf::CircleShape circle(16);
        // circle.setFillColor(colors[frame % max_colors]);
        circle.setFillColor(sf::Color(r, g, b, 255));
        rt.clear();
        rt.draw(circle);
        rt.display();

        window.clear(sf::Color::Black);
        window.draw(sp);
        window.display();
    }
}