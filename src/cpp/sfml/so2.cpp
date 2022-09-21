#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
        // RenderWindow window(VideoMode({width, height}), "Game - 1");
    sf::RenderWindow window(sf::VideoMode({ 640 ,480}), "Window");

    std::string input_text;
    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text text("", font);

    sf::Clock clock;
    sf::RectangleShape rectangle(sf::Vector2f(120, 50));
    rectangle.setSize(sf::Vector2f(100, 100));
    rectangle.setFillColor(sf::Color(150, 50, 250));
    rectangle.setOutlineThickness(10);
    rectangle.setOutlineColor(sf::Color(250, 150, 100));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::TextEntered) {
                if (std::isprint(event.text.unicode))
                    input_text += event.text.unicode;
            }
            else if (event.type == sf::Event::KeyPressed) {

                if (event.key.code == sf::Keyboard::Backspace) {
                    if (!input_text.empty())
                        input_text.pop_back();
                }
                if (event.key.code == sf::Keyboard::Enter) {
                    std::string text1 = text.getString().toAnsiString();
                    std::cout << text1 << std::endl;
                }
            }
        }

        static sf::Time text_effect_time;
        static bool show_cursor;

        text_effect_time += clock.restart();

        if (text_effect_time >= sf::seconds(0.5f))
        {
            show_cursor = !show_cursor;
            text_effect_time = sf::Time::Zero;
        }

        text.setString(input_text + (show_cursor ? '_' : ' '));

        window.clear();
        window.draw(rectangle);
        window.draw(text);
        window.display();
    }
}
