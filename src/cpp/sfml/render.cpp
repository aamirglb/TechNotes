#include <SFML/Graphics.hpp>
#include <iostream>

uint32_t winWidth {1080}, winHeight{840};

class Ball
{
public:
    Ball(float radius, float velocity, float posX, float posY)
        : _radius{radius}
        , _velocity{velocity, velocity}
    {
        shape.setPosition({posX, posY});
        shape.setRadius(_radius);
        shape.setFillColor(sf::Color::Red);
        shape.setOrigin({_radius, _radius});
    }

    const sf::CircleShape& getShape() const
    {
        return shape;
    }

    void update()
    {
        shape.move(_velocity);

        using namespace sf;
        if(Keyboard::isKeyPressed(Keyboard::Key::L) && left() > 0) {
            _velocity.x = -8.f;
        } else if(Keyboard::isKeyPressed(Keyboard::Key::K) && right() < winWidth) {
            _velocity.x = 8.f;
        } else if(Keyboard::isKeyPressed(Keyboard::Key::J) && top() > 0) {
            _velocity.y = -8.f;
        } else if(Keyboard::isKeyPressed(Keyboard::Key::H) && bottom() < winHeight) {
            _velocity.y = 8.f;
        } else {
            _velocity.x = 0;
            _velocity.y = 0;
        }

        // static float delta{10.f};
        // if(_radius > 120.f) {
        //     delta = -10.f;
        // } else if(_radius < 10.f) {
        //     delta = 10.f;
        // }
        // std::cout << _radius << " " << delta << std::endl;
        // _radius += delta;
        // shape.setRadius(_radius);
        // shape.setOrigin({_radius, _radius});
    }

    float x()      { return shape.getPosition().x; }
    float y()       { return shape.getPosition().y; }
    float left()    { return x() - shape.getRadius(); }
    float right()   { return x() + shape.getRadius(); }
    float top()     { return y() - shape.getRadius(); }
    float bottom()  { return y() + shape.getRadius(); }

private:
    sf::CircleShape shape;
    float _radius{10.f};
    sf::Vector2f _velocity{8.f, 8.f};
};

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
        shape.rotate(sf::degrees(-1.5f));
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
};

int main()
{
    sf::RenderWindow window(sf::VideoMode({winWidth, winHeight}), "Basics");
    window.setFramerateLimit(60);

    bool blackBackGround {true};
    Ball ball{10., 8., winWidth/2.f, winHeight/2.f};
    Brick brick{60.f, 20.f, winWidth/2.f, winHeight - 50.f};

    while(window.isOpen()) {
        sf::Event event;

        while(window.pollEvent(event)) {
            if(event.type == sf::Event::EventType::Closed)
                window.close();
            else if(event.type == sf::Event::EventType::KeyReleased) {
                if(event.key.code == sf::Keyboard::Key::Escape)
                    window.close();
            }
        }

        window.clear(blackBackGround ? sf::Color::Black : sf::Color::White);
        // blackBackGround = !blackBackGround;

        ball.update();
        brick.update();
        window.draw(ball.getShape());
        window.draw(brick.getShape());

        window.display();

        // sf::sleep(sf::milliseconds(500));
    }
}