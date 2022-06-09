#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>

const int32_t M{20};
const int32_t N{10};

int32_t field[M][N] = {0};

struct Point {
    int32_t x, y;
} a[4],b[4];

int32_t figures[7][4] {
    1,3,5,7,  // I
    2,4,5,7,  // Z
    3,5,4,6,  // S
    3,5,4,7,  // T
    2,3,5,7,  // L
    3,5,7,6,  // J
    2,3,4,5,  // O
};

bool check()
{
    for(int32_t i{}; i < 4; ++i){
        if(a[i].x < 0 || a[i].x >= N || a[i].y >= M) return 0;
        else if (field[a[i].y][a[i].x]) return 0;
    }
    return 1;
}

int main()
{
    srand(time(0));
    sf::RenderWindow window(sf::VideoMode({320*2, 480*2}), "Tetris Game");
    sf::Texture t;
    if(!t.loadFromFile("tiles_v2_0.png")) {
        std::cerr << "Unable to load tiles_v2_0.png" << std::endl;
        return -1;
    }
    sf::Sprite s(t);
    s.setTextureRect(sf::IntRect({0, 0}, {36, 36}));

    int dx{};
    bool rotate{};
    int32_t colorNum{1};
    float timer{}, delay{0.3f};

    sf::Clock clock;

    while(window.isOpen()) {

        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;
        sf::Event event;
        // int32_t n{0};

        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }

            if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Up) rotate = true;
                else if(event.key.code == sf::Keyboard::Left) dx = -1;
                else if(event.key.code == sf::Keyboard::Right) dx = 1;
            }
        }

        // Move
        for(int32_t i{}; i < 4; ++i) {
            b[i] = a[i];
            a[i].x += dx;
        }

        if(!check()) {
            for(int32_t i=0; i<4; ++i)
                a[i] = b[i];
        }

        // Rotate
        if(rotate) {
            Point p = a[1];
            for(int32_t i{}; i < 4; ++i) {
                int32_t x = a[i].y - p.y;
                int32_t y = a[i].x - p.x;
                a[i].x = p.x - x;
                a[i].y = p.y + y;
            }
            if(!check()) {
                for(int32_t i{}; i < 4; ++i) {
                    a[i] = b[i];
                }
            }
        }

        // Tick
        if(timer > delay) {
            for(int32_t i = 0; i < 4; ++i) {
                b[i] = a[i];
                a[i].y += 1;
            }

            if(!check()) {
                for(int32_t i{}; i < 4; ++i) {
                    field[b[i].y][b[i].x] = colorNum;
                }
                colorNum = 1+rand()%7;
                int32_t n = rand() % 7;
                for(int32_t i {}; i < 4; ++i) {
                    a[i].x = figures[n][i] % 2;
                    a[i].y = figures[n][i] / 2;
                }
            }
            timer = 0;
        }
        // if(a[0].x == 0)
        // for(int32_t i = 0; i < 4; ++i) {
        //     a[i].x = figures[n][i] % 2;
        //     a[i].y = figures[n][i] / 2;
        // }
        dx = 0; rotate = 0;

        ///// drawing
        window.clear(sf::Color::White);

        for(int32_t i{}; i < M; ++i) {
            for(int32_t j{}; j < N; ++j) {
                if(field[i][j] == 0) continue;
                s.setPosition({j*36, i*36});
                window.draw(s);
            }
        }
        // for(int32_t i = 0; i < 4; ++i) {
        //     s.setPosition(sf::Vector2f(a[i].x*36, a[i].y*36));
        //     window.draw(s);
        // }
        // window.draw(s);
        window.display();
    }
}