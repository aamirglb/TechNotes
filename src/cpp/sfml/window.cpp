#include <SFML/Window.hpp>
#include <iostream>

int main()
{
    sf::Window window(sf::VideoMode({300, 200}), "First Window", sf::Style::Default);
    auto modes = sf::VideoMode::getFullscreenModes();
    uint32_t count {};
    for(const auto mode : modes) {
        std::cout << ++count << ". ("
                  << mode.size.x << "x"
                  << mode.size.y << ") bpp: "
                  << mode.bitsPerPixel << std::endl;
    }

    auto desktop = sf::VideoMode::getDesktopMode();
    std::cout << "Desktop Mode: (" << desktop.size.x
              << "x" << desktop.size.y << ") bpp: "
              << desktop.bitsPerPixel << std::endl;

    // sf::sleep(sf::seconds(2));

    sf::String buffer;

    while (window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            switch(event.type) {
            case sf::Event::EventType::Closed:
                window.close();
                break;
            case sf::Event::EventType::TextEntered:
                buffer += event.text.unicode;
                break;
            case sf::Event::EventType::KeyPressed:
                if(event.key.code == sf::Keyboard::Key::Space)
                    window.setTitle("Space pressed");
                break;
            case sf::Event::EventType::KeyReleased:
                if(event.key.code == sf::Keyboard::Key::Enter) {
                    window.setTitle(buffer);
                    buffer.clear();
                }
                else if(event.key.code == sf::Keyboard::Key::Space)
                    window.setTitle("Space released");
                else if(event.key.code == sf::Keyboard::Key::Escape)
                    window.close();
                break;
            default:
                break;
            }
            // if(event.type == sf::Event::EventType::Closed) {
            //     window.close();
            // }
        }
    }

    return 0;
}