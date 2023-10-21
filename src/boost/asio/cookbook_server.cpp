#include <asio.hpp>
#include <iostream>
#include <fmt/core.h>

void process_request(asio::ip::tcp::socket &socket)
{
    asio::streambuf request;
    asio::error_code ec;

    asio::read(socket, request, ec);
    if (ec != asio::error::eof)
    {
        throw std::system_error(ec);
    }
    const char response[]{0x48, 0x69, 0x21};
    asio::write(socket, asio::buffer(response));
    socket.shutdown(asio::socket_base::shutdown_send);
}

int main()
{
    std::uint16_t server_port{3333};
    try
    {
        asio::ip::tcp::endpoint endpoint{asio::ip::address_v4::any(), server_port};
        asio::io_context io_ctx;
        asio::ip::tcp::acceptor acceptor{io_ctx, endpoint};
        asio::ip::tcp::socket socket(io_ctx);
        acceptor.accept(socket);
        process_request(socket);
    }
    catch (const std::system_error &e)
    {
        std::cerr << fmt::format("Error occured!. {}, {}", e.code().value(), e.what()) << std::endl;
        return e.code().value();
    }
}