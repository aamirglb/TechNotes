#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

const float TileSize {40.f};

int main()
{
    sf::TcpSocket socket;
    std::string input;
    std::cout << "Enter host or Ip address: ";
    std::cin >> input;

    if(input == "host") {
        sf::TcpListener listener;
        listener.listen(45000);
        std::cout << "Waiting for connection..." << std::endl;
        if(listener.accept(socket) != sf::Socket::Done) return -1;
    } else {
        std::cout << "Trying to connect..." << std::endl;
        if(socket.connect(input, 45000, sf::seconds(10)) != sf::Socket::Done) {
            return -1;
        }
    }

    // Setup the scene
    sf::RenderWindow window(sf::VideoMode({640, 480}), input);
    window.setFramerateLimit(60);
    socket.setBlocking(false);

    sf::Vector2f shapeSize({TileSize, TileSize});
    sf::RectangleShape localShape(shapeSize);
    localShape.setFillColor(sf::Color::Red);
    localShape.setPosition({40, 40});

    sf::RectangleShape remoteShape(shapeSize);
    remoteShape.setFillColor(sf::Color::Cyan);
    remoteShape.setPosition({80, 80});

    // game loop
    while(window.isOpen()) {
        sf::Vector2i moveDir;
        sf::Event event;

        while(window.pollEvent(event)) {
            switch(event.type) {
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::W)
                        moveDir.y += -1;
                    else if(event.key.code == sf::Keyboard::A)
                        moveDir.x += -1;
                    else if(event.key.code == sf::Keyboard::S)
                        moveDir.y += 1;
                    else if(event.key.code == sf::Keyboard::D)
                        moveDir.x += 1;
                    else if(event.key.code == sf::Keyboard::Escape)
                        window.close();
                break;
                case sf::Event::Closed:
                    window.close();
                    break;
            }

            sf::Packet packet;
            if(socket.receive(packet) == sf::Socket::Done) {
                sf::Vector2f pos;
                packet >> pos.x >> pos.y;
                remoteShape.setPosition(pos);
            }

            if(moveDir.x !=0 || moveDir.y != 0) {
                localShape.move({moveDir.x * TileSize, moveDir.y * TileSize});
                sf::Packet packet;
                packet << localShape.getPosition().x << localShape.getPosition().y;
                if(socket.send(packet) != sf::Socket::Done) {
                    return -1;
                }
            }

            window.clear(sf::Color::Black);
            window.draw(localShape);
            window.draw(remoteShape);
            window.display();
        }
    }
}
