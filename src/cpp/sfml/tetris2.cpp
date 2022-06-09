#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>

const int32_t M{20};
const int32_t N{10};

int32_t field[M][N] = {0};

struct Point {
    int32_t x, y;
} a[4],b[4];

int32_t figures[9][4] {
    1,3,5,7,  // I
    2,4,5,7,  // Z
    3,5,4,6,  // S
    3,5,4,7,  // T
    2,4,5,6,
    2,3,5,7,  // L
    3,5,7,6,  // J
    2,3,4,5,  // O
    5,6,7,8,
};

int main()
{
    sf::RenderWindow window(sf::VideoMode({320*2, 480*2}), "Tetris Game");
    sf::Texture t;
    if(!t.loadFromFile("tiles_v2_0.png")) {
        std::cerr << "Unable to load tiles_v2_0.png" << std::endl;
        return -1;
    }
    sf::Sprite s(t);

    s.setTextureRect(sf::IntRect({0, 0}, {36, 36}));
    int32_t tile{};
    bool finish{};

    while(window.isOpen()) {
        sf::Event event;

        while(tile < 7 && !finish) {
            s.setTextureRect(sf::IntRect({tile*36, 0}, {36, 36}));
            ++tile;
            if(tile == 7) tile = 0;

            int32_t n{0};

            while(n < 8 && !finish) {
                std::cout << "tile = " << tile << " n = " << n << std::endl;
                while(window.pollEvent(event)) {
                    if(event.type == sf::Event::Closed) {
                        window.close();
                        finish = true;
                    }
                }

                for(int32_t i = 0; i < 4; ++i) {
                    a[i].x = figures[n][i] % 2;
                    a[i].y = figures[n][i] / 2;
                }
                window.clear(sf::Color::White);

                for(int32_t i = 0; i < 4; ++i) {
                    s.setPosition(sf::Vector2f(a[i].x*36, a[i].y*36));
                    window.draw(s);
                }
                // window.draw(s);
                window.display();
                sf::sleep(sf::seconds(0.5f));
                ++n;
            }
        }
    }
}