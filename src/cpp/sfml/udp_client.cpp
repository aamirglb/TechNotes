#include <SFML/Network.hpp>
#include <iostream>
#include <cstring>

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

int main(int argc, char *argv[]) {
    sf::UdpSocket socket;

    if(argc < 2) {
        sf::Packet packet;
        sf::Vector2f pos{1.45f, .54f};
        sf::String name{"Enemy"};
        sf::Int16 id { 1000};

        // packet << id << name << pos.x << pos.y;
        Client_Settings c;
        c.isHost = false;
        c.playerID = "Player-1";
        c.serverSettings.id = 101;
        c.serverSettings.name = "Server-1";
        packet << c;


        char message[] {"SFML UDP: Client-Server example."};
        // if(socket.send(message, sizeof(message), "127.0.0.1", 45000) != sf::Socket::Done) {
            if(socket.send(packet, "127.0.0.1", 45000) != sf::Socket::Done) {
            return -1;
        }
    } else {
        std::cout << argv[1] << ": " << sizeof(argv[1]) << std::endl;
        if(socket.send(argv[1], strlen(argv[1]), "127.0.0.1", 45000) != sf::Socket::Done) {
            return -1;
        }
    }
}
