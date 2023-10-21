#include <asio.hpp>
#include <iostream>
#include <fmt/core.h>

int main()
{
    const int BACKLOG_SIZE{30};
    std::uint16_t port{3333};
    asio::ip::tcp::endpoint endpoint{asio::ip::address_v4::any(), port};
    asio::io_context io_ctx;

    asio::ip::tcp::acceptor acceptor{io_ctx, endpoint.protocol()};
    asio::error_code ec;
    acceptor.bind(endpoint, ec);
    acceptor.listen(BACKLOG_SIZE, ec);
    asio::ip::tcp::socket sock(io_ctx);
    acceptor.accept(sock);
}