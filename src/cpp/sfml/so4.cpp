#include <SFML/Graphics.hpp>
#include <iostream>

// int main() {
//     // Window
//         // Main Window
//     sf::RenderWindow window(sf::VideoMode({900, 600}), "Conecept"); //, sf::Style::Default, window_settings);

//     sf::Image image;
//     image.create({30, 30}, sf::Color::White);
//     if (!image.saveToFile("result.bmp")) printf("Error >:(\n");

//     return 0;
// }

#include <iostream>

using namespace std;

int main() {
    int num, row, integ;

    cout << "Please enter size: ";
    cin >> integ;

    for (row = 1; row <= integ; row++) {
        for (num = 1; num <= integ - row + 1; num++) {
            cout << num;
        }
        for (; num <= integ; num++) {
            cout << "*";
        }
        cout << endl;
    }
}

// int main(){
//     sf::RenderWindow window(sf::VideoMode({1000, 700}), "project");
//     window.setFramerateLimit(60);

//     sf::RectangleShape rect;

//     int w = 100;
//     int h = 100;
//     rect.setSize(sf::Vector2f(w, h));

//     sf::Vector2f rectangle_position(500 - (w/2), 300 - (h/2));
//     rect.setPosition(rectangle_position);

//     float x_velocity = 3;
//     float y_velocity = 3;
// bool start {};
//    while (window.isOpen()) {

//            sf::Event event;
//            while (window.pollEvent(event)) {


//                if (event.type == sf::Event::Closed) window.close();

//                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
//                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) start = true;
//            }
//             if(start) {
//            if (rectangle_position.x > 1000 - w) {
//                x_velocity = x_velocity * -1;
//            }

//            if (rectangle_position.x < 1 ) {
//                x_velocity = x_velocity * -1;
//            }

//            if (rectangle_position.y > 700 - h) {
//                 rectangle_position.y -= 3;
//                y_velocity = y_velocity * -1;
//            }

//            if (rectangle_position.y < 50) {
//                y_velocity = y_velocity * -1;
//            }

//                y_velocity = y_velocity + 3;

//            rectangle_position.x = rectangle_position.x + x_velocity;
//            rectangle_position.y = rectangle_position.y + y_velocity;
//            rect.setPosition(rectangle_position);
//             }
//            window.clear();
//            window.draw(rect);

//            window.display();
//     }

// }

// int main(){
//     sf::RenderWindow window(sf::VideoMode({1000, 700}), "project");
//     window.setFramerateLimit(30);

//     sf::RectangleShape rect;

//     int w = 100;
//     int h = 100;
//     rect.setSize(sf::Vector2f(w, h));

//     sf::Vector2f rectangle_position(500 - (w/2), 300 - (h/2));
//     rect.setPosition(rectangle_position);

//     float x_velocity = 3;
//     float y_velocity = 3;
//     float y_delta = 3;

// static uint32_t cnt{};
//    while (window.isOpen()) {
// ++cnt;
//            sf::Event event;
//            while (window.pollEvent(event)) {


//                if (event.type == sf::Event::Closed) window.close();

//                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
//            }



//                y_velocity = y_velocity + y_delta;


//            rectangle_position.x = rectangle_position.x + x_velocity;
//            rectangle_position.y = rectangle_position.y + y_velocity;

//             if (rectangle_position.x > 1000 - w) {
//                x_velocity = x_velocity * -1;
//            }

//            if (rectangle_position.x < 1 ) {
//                x_velocity = x_velocity * -1;
//            }

//            if ((rectangle_position.y) > 700 - h) {
//             // y_velocity -= y_delta;

//                 // rectangle_position.y = 700 - h;
//                 // y_velocity -= y_delta;
//                 rectangle_position.y -= y_delta;
//                 y_velocity = y_velocity * -1;
//                 // if(rectangle_position.y + y_velocity + 3 < (700 - h)) {
//                 //     y_velocity = y_velocity * -1;
//                 // }
//                 // else {
//                 //     std::cout << "hit the else part\n";
//                 //     y_velocity = 0;
//                 //     y_delta = 0;
//                 // }
//            }

//            if (rectangle_position.y < 50) {
//                y_velocity = y_velocity * -1;
//            }
//             if(1 /*cnt % 10 == 0*/) {
//                 std::cout << rectangle_position.y << ", " << y_velocity << std::endl;
//             }
//            rect.setPosition(rectangle_position);


//            window.clear();
//            window.draw(rect);

//            window.display();
//     }

// }