#include <asio.hpp>
#include <fmt/core.h>
#include <iostream>

int main()
{
    std::string server_ip{"127.0.0.1"};
    std::uint16_t server_port{3333};

    asio::ip::tcp::endpoint endpoint{asio::ip::address::from_string(server_ip), server_port};
    asio::io_context io_ctx;
    asio::ip::tcp::socket sock(io_ctx, endpoint.protocol());
    asio::error_code ec;
    sock.connect(endpoint, ec);

    if (ec.value() != 0)
    {
        std::cout << fmt::format("Unable to connect to server. {}, {}", ec.value(), ec.message()) << std::endl;
        return ec.value();
    }
    else
    {
        std::cout << "Connected to server." << std::endl;
    }
}
