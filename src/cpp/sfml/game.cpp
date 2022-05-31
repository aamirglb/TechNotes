// clang++ -o game -std=c++20 -O3 -lsfml-system
//     -lsfml-graphics -lsfml-window -lsfml-autio game.cpp
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>

using namespace std;
using namespace sf;

constexpr int32_t width{800}, height{600};
constexpr float ballRadius{10.f}, ballVelocity{8.f};
constexpr float paddleWidth{60.f}, paddleHeight{20.f}, paddleVelocity{6.f};

constexpr float blockWidth{60.f}, blockHeight{20.f};
constexpr int32_t countBlockX{11}, countBlockY{4};


class Ball
{
public:
    CircleShape shape;
    Vector2f  velocity{-ballVelocity, -ballVelocity};
    Color ballColor{ Color::Red };

    Ball(float mX, float mY) {
        shape.setPosition({mX, mY});
        shape.setRadius(ballRadius);
        shape.setFillColor(ballColor);
        shape.setOrigin({ballRadius, ballRadius});
    }

    void update() {
        shape.move(velocity);

        if(left() < 0) { velocity.x = ballVelocity; ballColor = Color::White; }
        else if(right() > width) { velocity.x = -ballVelocity; ballColor = Color::Blue; }

        if(top() < 0) { velocity.y = ballVelocity; ballColor = Color::Yellow; }
        else if(bottom() > height) { velocity.y = -ballVelocity; ballColor = Color::Magenta; }

        shape.setFillColor(ballColor);
    }

    float x()      { return shape.getPosition().x; }
    float y()       { return shape.getPosition().y; }
    float left()    { return x() - shape.getRadius(); }
    float right()   { return x() + shape.getRadius(); }
    float top()     { return y() - shape.getRadius(); }
    float bottom()  { return y() + shape.getRadius(); }
};

class Paddle
{
public:
    RectangleShape shape;
    Vector2f velocity;

    Paddle(float mX, float mY) {
        shape.setPosition({mX, mY});
        shape.setSize({paddleWidth, paddleHeight});
        shape.setFillColor(Color::Red);
        shape.setOrigin({paddleWidth/2.f, paddleHeight/2.f});
    }

    void update() {
        shape.move(velocity);

        if(Keyboard::isKeyPressed(Keyboard::Key::Left)
            && left() > 0) {
            velocity.x = -paddleVelocity;
        } else if(Keyboard::isKeyPressed(Keyboard::Key::Right)
            && right() < width) {
            velocity.x = paddleVelocity;
        } else velocity.x = 0;
    }

    float x()       { return shape.getPosition().x; }
    float y()       { return shape.getPosition().y; }
    float left()    { return x() - shape.getSize().x / 2.f; }
    float right()   { return x() + shape.getSize().x / 2.f; }
    float top()     { return y() - shape.getSize().y / 2.f; }
    float bottom()  { return y() + shape.getSize().y / 2.f; }
};

class Brick
{
public:
    RectangleShape shape;
    bool destroyed{false};

    Brick(float mX, float mY) {
        shape.setPosition({mX, mY});
        shape.setSize({blockWidth, blockHeight});
        shape.setFillColor(Color::Cyan);
        shape.setOrigin({blockWidth/2.f, blockHeight/2.f});
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
    } else {
        mBall.velocity.x = ballVelocity;
    }
}

void testCollision(Brick& mBrick, Ball& mBall) {
    if(!isIntersecting(mBrick, mBall)) return;

    mBrick.destroyed = true;

    float overlapLeft{mBall.right() - mBrick.left()};
    float overlapRigth{mBrick.right() - mBall.left()};
    float overlapTop{mBall.bottom() - mBrick.top()};
    float overlapBottom{mBrick.bottom() - mBall.top()};

    bool ballFromLeft{abs(overlapLeft) < abs(overlapRigth)};
    bool ballFromTop{abs(overlapTop) < abs(overlapBottom)};

    float minOverlapX{ballFromLeft ? overlapLeft : overlapRigth};
    float minOverlapY{ballFromTop ? overlapTop : overlapBottom};

    if(abs(minOverlapX) < abs(minOverlapY))
        mBall.velocity.x = ballFromLeft ? -ballVelocity : ballVelocity;
    else
        mBall.velocity.y = ballFromTop ? -ballVelocity : ballVelocity;
}
int main()
{
    Ball ball{width/2, height/2};
    Paddle paddle(width/2, height - 50);

    vector<Brick> bricks;
    for(auto r{0}; r < countBlockX; ++r) {
        for(auto c{0}; c < countBlockY; ++c) {
            bricks.emplace_back(
                (r + 1) * (blockWidth + 3) + 22,
                (c + 2) * (blockHeight + 3));
        }
    }

    RenderWindow window(VideoMode({width, height}), "Game - 1");
    window.setFramerateLimit(60);

    while(true) {
        window.clear(Color::Black);

        if(Keyboard::isKeyPressed(Keyboard::Key::Escape))
            break;

        ball.update();
        paddle.update();

        testCollision(paddle, ball);

        for(auto& brick : bricks) testCollision(brick, ball);

        bricks.erase(remove_if(begin(bricks), end(bricks),
            [](const auto& brick) { return brick.destroyed; }),
            end(bricks));

        window.draw(ball.shape);
        window.draw(paddle.shape);
        for(auto& brick : bricks) window.draw(brick.shape);
        window.display();
    }
}