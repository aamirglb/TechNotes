#include <asio.hpp>
#include <iostream>
#include <fmt/core.h>

void communicate(asio::ip::tcp::socket &socket)
{
    const char request[]{0x48, 0x65, 0x0, 0x6c, 0x6c, 0x6f};
    asio::write(socket, asio::buffer(request));
    socket.shutdown(asio::socket_base::shutdown_send);
    asio::streambuf response;

    asio::error_code ec;
    asio::read(socket, response, ec);

    if (ec == asio::error::eof)
    {
        std::cout << "client received entire response from server." << std::endl;
    }
    else
    {
        throw std::system_error(ec);
    }
}

int main()
{
    std::string server_ip{"127.0.0.1"};
    std::uint16_t port{3333};
    try
    {
        asio::ip::tcp::endpoint endpoint{asio::ip::address::from_string(server_ip), port};
        asio::io_context io_ctx;
        asio::ip::tcp::socket socket(io_ctx, endpoint.protocol());
        socket.connect(endpoint);
        communicate(socket);
    }
    catch (const std::system_error &e)
    {
        std::cerr << fmt::format("Error: {}, {}", e.code().value(), e.what()) << std::endl;
        return e.code().value();
    }
}