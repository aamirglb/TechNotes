#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode({1080, 720}), "Image");
    window.setFramerateLimit(30);

    sf::Image image;
    image.create({200, 200}, sf::Color::Red);

    sf::Texture texture;
    if(!texture.loadFromImage(image))
        return -1;

    sf::RectangleShape rect({300, 150});
    rect.setTexture(&texture);

    sf::Texture t2;
    if(!t2.loadFromFile("green-leaf.png")) {
        std::cout << "Unable to load file" << std::endl;
        return -1;
    }
    sf::ConvexShape shape(5);
    shape.setPoint(0, {0, 0});
    shape.setPoint(1, {200, 0});
    shape.setPoint(2, {180, 120});
    shape.setPoint(3, {100, 200});
    shape.setPoint(4, {20, 120});
    shape.setTexture(&t2);
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color::Red);
    shape.move({1080/2, 720/2});

    std::cout << sf::Texture::getMaximumSize() << std::endl;

    sf::Texture t3;
    if(!t3.loadFromFile("tile.png")) {
        std::cout << "Unable to load tile.png\n";
        return -1;
    }
    t3.setRepeated(true);

    sf::RectangleShape rect2({102 * 3, 181 * 2});
    rect2.setTextureRect(sf::IntRect({0, 0}, {102 * 3, 181 * 2}));
    rect2.setTexture(&t3);
    rect2.move({10, 200});

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            window.close();

        window.clear(sf::Color::Black);
        window.draw(rect);
        window.draw(shape);
        window.draw(rect2);
        window.display();
    }
}