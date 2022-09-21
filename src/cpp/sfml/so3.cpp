#include <iostream>
#include <string>
#include <SFML/Network.hpp>
using namespace std;

int main()
{
    //const sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    string ip = "127.0.0.1";
    sf::TcpSocket socket;
    string text = " con to ";
    char connectionType, mode;
    char buffer[2000];
    size_t received;
    cout << " c :";
    cin >> connectionType;
    if (connectionType == 's')
    {
        sf::TcpListener listener;
        listener.listen(2000);
        listener.accept(socket);
        text += "server";

    }
    else if (connectionType == 'c') {
        socket.connect(sf::IpAddress(ip), 2000);
        text += "client";
    }
    socket.send(text.c_str(), text.length() + 1);
    socket.receive(buffer, sizeof(buffer), received);
    cout << buffer << endl;
    system("pause");
    return 0;

}