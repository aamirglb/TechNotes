// cl /std:c++17 /I c:/sw/SFML/include so_shader.cpp /link /LIBPATH:"c:/sw/SFML/lib/msvc" sfml-graphics-d.lib sfml-window-d.lib sfml-system-d.lib
#include <SFML/Graphics.hpp>
int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    sf::Shader shader;
    shader.loadFromFile("vertex_shader.vert", "fragment_shader.frag");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape, &shader);
        window.display();
    }

    return 0;
}
