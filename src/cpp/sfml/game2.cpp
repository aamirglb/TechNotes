#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

uint32_t winWidth {1080}, winHeight{840};
const float boxWidth { winWidth * .8f };
const float boxHeight { winHeight * .9f };
constexpr sf::Vector2f boxTopLeft {10.f, 10.f};
constexpr float ballRadius{10.f}, ballVelocity{8.f};
constexpr float paddleWidth{100.f}, paddleHeight{20.f}, paddleVelocity{8.f};

class Ball
{
public:
    sf::CircleShape  shape;
    sf::Vector2f    velocity{-ballVelocity, -ballVelocity};
    sf::Color       ballColor{sf::Color::Red};
    uint32_t        miss{};
    uint32_t        hit{};

    Ball(float posX, float posY) {
        shape.setPosition({posX, posY});
        shape.setRadius(ballRadius);
        shape.setFillColor(sf::Color::Red);
        shape.setOrigin({ballRadius, ballRadius});
    }

    void update() {
        shape.move(velocity);

        if(left() < boxTopLeft.x) {
            velocity.x = ballVelocity;
        } else if(right() > boxWidth) {
            velocity.x = -ballVelocity;
        }

        if(top() < boxTopLeft.y) {
            velocity.y = ballVelocity;
        } else if(bottom() > boxHeight) {
            velocity.y = -ballVelocity;
            ++miss;
        }
    }

    float x()      { return shape.getPosition().x; }
    float y()       { return shape.getPosition().y; }
    float left()    { return x() - shape.getRadius(); }
    float right()   { return x() + shape.getRadius(); }
    float top()     { return y() - shape.getRadius(); }
    float bottom()  { return y() + shape.getRadius(); }
    std::pair<uint32_t, uint32_t> getScore() const {
        return std::make_pair(hit, miss);
    }
};

class Paddle
{
public:
    sf::RectangleShape    shape;
    sf::Vector2f       velocity{1, 0};

    Paddle(float posX, float posY) {
        shape.setPosition({posX, posY});
        shape.setSize({paddleWidth, paddleHeight});
        shape.setFillColor(sf::Color::Cyan);
        shape.setOrigin({paddleWidth/2.f, paddleHeight/2.f});
    }

    void update() {
        shape.move(velocity);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)
            && left() > 12) {
                velocity.x = -paddleVelocity;
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)
            && right() < boxWidth) {
                velocity.x = paddleVelocity;
        } else {
            velocity.x = 0;
        }
    }

    float x()       { return shape.getPosition().x; }
    float y()       { return shape.getPosition().y; }
    float left()    { return x() - shape.getSize().x / 2.f; }
    float right()   { return x() + shape.getSize().x / 2.f; }
    float top()     { return y() - shape.getSize().y / 2.f; }
    float bottom()  { return y() + shape.getSize().y / 2.f; }
};

template<typename T1, typename T2>
bool isIntersecting(T1 &mA, T2 &mB) {
    return mA.right() >= mB.left() && mA.left() <= mB.right()
        && mA.bottom() >= mB.top() && mA.top() <= mB.bottom();
}

void testCollision(Paddle& mPaddle, Ball& mBall) {
    if(!isIntersecting(mPaddle, mBall)) return;

    mBall.velocity.y = -ballVelocity;

    if(mBall.x() < mPaddle.x()) {
        mBall.velocity.x = -ballVelocity;
        ++mBall.hit;
    } else {
        mBall.velocity.x = ballVelocity;
        ++mBall.hit;
    }
}

class ScoreBoard
{
public:
    sf::Font font_;
    sf::Text text;

    ScoreBoard(std::string font)
    {
        if(!font_.loadFromFile(font)) {
            std::cerr << "Unable to load fonts";
            throw std::invalid_argument("Resource not available");
        }
        text.setFont(font_);
        text.setFillColor(sf::Color::White);
        text.move({boxTopLeft.x+boxWidth+10, boxTopLeft.y});
    }

    void setScore(std::pair<uint32_t, uint32_t> score) {
        std::stringstream ss;
        ss << "Hits: " << score.first << "\n" << "Miss: " << score.second;
        text.setString(ss.str());
    }
};

int main()
{
    Ball ball{boxWidth / 2, boxHeight / 2};
    Paddle paddle(boxWidth/2, boxHeight - 50);

    ScoreBoard board{"arial.ttf"};
    board.setScore({0, 0});

    sf::RenderWindow window(sf::VideoMode({winWidth, winHeight}), "Game");
    window.setFramerateLimit(60);

    sf::RectangleShape box({boxWidth, boxHeight});
    box.setFillColor(sf::Color::Transparent);
    box.setOutlineColor(sf::Color::White);
    box.setOutlineThickness(2);
    box.move(boxTopLeft);

    while(window.isOpen()) {
        sf::Event e;

        while(window.pollEvent(e)) {
            if(e.type == sf::Event::EventType::Closed)
                window.close();
            else if(e.type == sf::Event::EventType::KeyReleased &&
                    e.key.code == sf::Keyboard::Key::Escape) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        ball.update();
        paddle.update();

        testCollision(paddle, ball);

        board.setScore(ball.getScore());

        window.draw(box);
        window.draw(ball.shape);
        window.draw(paddle.shape);
        window.draw(board.text);
        window.display();
    }
}