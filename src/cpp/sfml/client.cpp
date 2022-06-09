#include <SFML/Network.hpp>
#include <iostream>

int main() {
    sf::TcpSocket socket;

    sf::Socket::Status status = socket.connect("127.0.0.1", 45000);
    if (status != sf::Socket::Done) {
        return -1;
    }

    char message[] {"SFML: Client-Server example."};
    if(socket.send(message, sizeof(message)) != sf::Socket::Done) {
        return -1;
    }
}
