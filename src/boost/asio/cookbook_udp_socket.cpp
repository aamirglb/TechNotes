#include <iostream>
#include <asio.hpp>

int main()
{
    std::uint16_t port{3333};
    asio::ip::udp::endpoint endpoint{asio::ip::address_v4::any(), port};
    asio::io_context io_ctx;
    asio::ip::udp::socket sock(io_ctx, endpoint.protocol());
    asio::error_code ec;
    sock.bind(endpoint, ec);
    if (ec.value() != 0)
    {
        std::cout << "Failed to bind socket. Error: " << ec.value() << ", " << ec.message() << std::endl;
        return ec.value();
    }
    else
    {
        std::cout << endpoint << " bond successfully." << std::endl;
    }
}