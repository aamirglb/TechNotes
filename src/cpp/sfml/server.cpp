#include <SFML/Network.hpp>
#include <iostream>

int main()
{
    sf::TcpListener listener;
    listener.listen(45000);

    sf::TcpSocket socket;
    if(listener.accept(socket) != sf::Socket::Done)
        return -1;

    sf::sleep(sf::seconds(1));

    const size_t size{100};
    char data[size];
    size_t readSize;
    if(socket.receive(data, size, readSize) != sf::Socket::Done) {
        return -1;
    }
    std::cout << data <<std::endl;
}