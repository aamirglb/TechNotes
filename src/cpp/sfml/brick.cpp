#include <SFML/Graphics.hpp>
#include <iostream>

uint32_t winWidth {1080}, winHeight{840};


class Brick
{
public:
    Brick(float width, float height, float posX, float posY)
        : _w{width}
        , _h{height}
        , _pos{posX, posY}
    {
        shape.setPosition({posX, posY});
        shape.setSize({_w, _h});
        shape.setFillColor(sf::Color::Cyan);
        shape.setOrigin({_w/2.f, _h/2.f});
    }

    void destroyBrick() {
        _destroy = true;
    }

    void update()
    {
        shape.move(_velocity);
        using namespace sf;

        if(Keyboard::isKeyPressed(Keyboard::Key::Left) && left() > 0) {
            _velocity.x = -6.f;
        } else if(Keyboard::isKeyPressed(Keyboard::Key::Right) && right() < winWidth) {
            _velocity.x = 6.f;
        } else if(Keyboard::isKeyPressed(Keyboard::Key::Up) && top() > 0) {
            _velocity.y = -6.f;
        } else if(Keyboard::isKeyPressed(Keyboard::Key::Down) && bottom() < winHeight) {
            _velocity.y = 6.f;
        } else {
            _velocity.x = 0;
            _velocity.y = 0;
        }

        if(_destroy) {
            _w -= (_w * .1);
            _h -= (_h * .1);
            shape.setSize({_w, _h});
            shape.setPosition(_pos);
            shape.setOrigin({_w/2.f, _h/2.f});
        }
    }

    const sf::RectangleShape& getShape() const
    {
        return shape;
    }

    float x()       { return shape.getPosition().x; }
    float y()       { return shape.getPosition().y; }
    float left()    { return x() - shape.getSize().x / 2.f; }
    float right()   { return x() + shape.getSize().x / 2.f; }
    float top()     { return y() - shape.getSize().y / 2.f; }
    float bottom()  { return y() + shape.getSize().y / 2.f; }

private:
    sf::RectangleShape shape;
    float _w, _h;
    sf::Vector2f _pos;
    sf::Vector2f _velocity;
    bool _destroy{};
};

int main()
{
    sf::RenderWindow window(sf::VideoMode({winWidth, winHeight}), "Basics");
    window.setFramerateLimit(60);

    bool blackBackGround {true};
    Brick brick{60.f, 20.f, winWidth/2.f, winHeight/2.f};

    while(window.isOpen()) {
        sf::Event event;

        while(window.pollEvent(event)) {
            if(event.type == sf::Event::EventType::Closed)
                window.close();
            else if(event.type == sf::Event::EventType::KeyReleased) {
                if(event.key.code == sf::Keyboard::Key::Escape)
                    window.close();
                else if(event.key.code == sf::Keyboard::Key::Space) {
                    brick.destroyBrick();
                }
            }
        }

        window.clear(blackBackGround ? sf::Color::Black : sf::Color::White);;

        brick.update();
        window.draw(brick.getShape());

        window.display();

        // sf::sleep(sf::milliseconds(500));
    }
}