#include "mainMenu.hpp"

mainMenu::mainMenu()
: State()
{

    // if (!font.loadFromFile("./assets/pixelletters.ttf")) {
    if (!font.loadFromFile("./PixellettersFull.ttf")) {
        cout << "Couldn't load font" << endl;
    }

    // Exit
    options[0].setFont(font);
    options[0].setString("Exit");
    options[0].setPosition({35, 35});
    options[0].setFillColor(Color::White);
    options[0].setCharacterSize(60);

    // Sorts
    options[1].setFont(font);
    options[1].setString("Sorts");
    options[1].setPosition({screenWidth*0.05f, screenHeight*0.4f});
    options[1].setFillColor(Color::White);
    options[1].setCharacterSize(60);

    // Graphs
    options[2].setFont(font);
    options[2].setString("Graphs");
    options[2].setPosition({screenWidth*0.05f, screenHeight*0.6f});
    options[2].setFillColor(Color::White);
    options[2].setCharacterSize(60);

    // Title
    options[3].setFont(font);
    options[3].setString("Algorithm Visualizer");
    options[3].setPosition({screenWidth/4.f, screenHeight*0.2f});
    options[3].setFillColor(Color::White);
    options[3].setCharacterSize(70);
}

void mainMenu::draw(RenderWindow &window)
{
    for(int i=0; i<MENU_OPTIONS; i++)
    {
        window.draw(options[i]);
    }
    window.display();
}