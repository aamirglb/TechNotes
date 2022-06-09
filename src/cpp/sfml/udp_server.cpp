#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>

struct Server_Settings {
    std::string name;
    uint16_t  id;
};

struct Client_Settings
{
    Server_Settings serverSettings;
    std::string playerID;
    bool isHost;

    friend sf::Packet& operator<<(sf::Packet& p, const Client_Settings &c) {
        p << c.serverSettings.name
          << c.serverSettings.id
          << c.playerID
          << c.isHost;
        return p;
    }

    friend sf::Packet& operator>>(sf::Packet& p, Client_Settings &c) {
        p >> c.serverSettings.name
          >> c.serverSettings.id
          >> c.playerID
          >> c.isHost;
        return p;
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode({640, 480}), "Shapes");
    window.setFramerateLimit(10);

    sf::Font font;
    if(!font.loadFromFile("arial.ttf"))
        return -1;

    sf::Text text("", font);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    sf::UdpSocket socket;
    socket.bind(45000);
    socket.setBlocking(false);

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

        // const size_t size{100};
        // char data[size] {};
        size_t readSize;
        sf::IpAddress senderIP;
        uint16_t remotePort;

        sf::Packet packet;
        // sf::Vector2f pos;
        // sf::String name;
        // sf::Int16 id;

        Client_Settings c;
        if(socket.receive(packet, senderIP, remotePort) == sf::Socket::Done) {
            // packet >> id >> name >> pos.x >> pos.y;
            packet >> c;
            std::cout << "host: " << c.isHost << std::endl
                      << "player-id: " << c.playerID << std::endl
                      << "server-id: " << c.serverSettings.id << std::endl
                      << "name: " << c.serverSettings.name << std::endl;

            // std::cout << id << " " << name.toAnsiString() << " " << pos.x << " " << pos.y << std::endl;
            // text.setString(data);
            // std::cout << "Received data from " << senderIP << " on " << remotePort << std::endl;
            // std::cout << data << std::endl;
        }

        window.clear(sf::Color::Black);
        window.draw(text);
        window.display();

    }
}