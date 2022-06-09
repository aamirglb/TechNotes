#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

class someText{
private:
    Font _font;
    Text _text;

public:
    someText() {}
    someText(string str) {
        [[maybe_unused]] auto b = _font.loadFromFile("arial.ttf");
        _text.setFont(_font);
        _text.setString(str);
        _text.setFillColor(Color::Black);
    }
    ~someText() {}
    void drawText(RenderWindow& win) {
        win.draw(_text);
    }
};

int main()
{
    //create a window
    RenderWindow window(VideoMode({500, 500}), "SFML", Style::Default);
    window.setFramerateLimit(10);

    Font font;
    if(!font.loadFromFile("arial.ttf")) return -1;
    Text t("Look at aerial font.", font);
    t.setStyle(Text::Bold | Text::Underlined);

    string textValue[3] = {"un","dos","tres"};
    someText textArray[3];

    //create someText objects and store them in an array
    for (int i = 0; i < 3; i++) {
        someText obj(textValue[i]);
        textArray[i] = obj;
    }

    //main loop
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

        window.clear(Color::Black);
        //draw text
        // window.draw(t);
        for (int i = 0; i < 3; i++) {
            textArray[i].drawText(window);
        }
        window.display();
    }

    return 0;
}

