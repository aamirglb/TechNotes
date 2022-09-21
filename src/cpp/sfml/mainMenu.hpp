#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include <SFML/Graphics.hpp>
using namespace sf;
#include <iostream>
using namespace std;

#define MENU_OPTIONS 4

class State {
public:
    int32_t screenWidth;
    int32_t screenHeight;

    State() {
        screenWidth = 1000;
        screenHeight = 800;
    }
};

class mainMenu : public State {
protected:
    Text options[MENU_OPTIONS];
    Font font;

public:
    mainMenu();
    void draw(RenderWindow &window);
};

#endif