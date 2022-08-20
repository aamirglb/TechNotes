#include <boost/asio.hpp>
#include <array>
#include <iostream>

int main() {
    uint16_t port{15001};
    boost::asio::io_context io_context;
    boost::asio::ip::udp::endpoint receiver(boost::asio::ip::udp::v4(), port);
    boost::asio::ip::udp::socket socket(io_context, receiver);
    std::cout << "Echo server waiting for message on 15001.\n";

    while(true) {
       std::array<uint8_t, 65536> buffer;
       boost::asio::ip::udp::endpoint sender;
       size_t byte_rx = socket.receive_from(boost::asio::buffer(buffer), sender);
       for(size_t i = 0; i < byte_rx; ++i) std::cout << buffer[i];
       std::cout << std::endl;
       socket.send_to(boost::asio::buffer(buffer), sender);
    }
}