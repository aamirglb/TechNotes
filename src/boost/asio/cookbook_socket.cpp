#include <asio.hpp>
#include <iostream>

int main()
{
    std::uint16_t port{3333};
    asio::io_context io_ctx;
    asio::ip::tcp::endpoint endpoint(asio::ip::address_v4::any(), port);

    asio::ip::tcp::acceptor acceptor{io_ctx, endpoint.protocol()};
    asio::error_code ec;
    acceptor.bind(endpoint, ec);
    if (ec.value() != 0)
    {
        std::cout << "failed to bind acceptor socket."
                  << "Error Code: " << ec.value() << ", Message: " << ec.message() << std::endl;
        return ec.value();
    }
    // asio::ip::tcp protocol = asio::ip::tcp::v4();
    // asio::ip::tcp::socket sock(io_ctx);
    // asio::error_code ec;
    // sock.open(protocol, ec);

    // if (ec.value() != 0)
    // {
    //     std::cout << "Failed to open the socket!! Error code = " << ec.value() << ". Message: " << ec.message() << std::endl;
    // }
    // else
    // {
    //     std::cout << "socket opened successfully." << std::endl;
    // }
}