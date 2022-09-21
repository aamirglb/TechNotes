#include "mainMenu.hpp"

int main()
{
    RenderWindow window(VideoMode({1000, 800}), "Visualizer");
    mainMenu menu = mainMenu();
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear(Color(255, 0, 255));
        menu.draw(window);
    }
    return 0;
}