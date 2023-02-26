#include <boost/asio/co_spawn.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/awaitable.hpp>
#include <boost/asio.hpp>
#include <string>
#include <iostream>

using namespace std;
namespace asio = boost::asio;
using namespace boost::asio::ip;

asio::awaitable<void> handle_connection(tcp::socket &&stream)
{
    std::cout << "new connection\n";
    std::string buffer;
    uint64_t buffer_size;

    while (stream.is_open())
    {
        co_await stream.async_receive(asio::buffer(&buffer_size, 8), asio::use_awaitable);
        buffer = std::string(buffer_size, '\0');
        std::cout << "message size: " << buffer_size << "\n";
        co_await stream.async_receive(asio::buffer(buffer, buffer_size), asio::use_awaitable);
        std::cout << "new message: " << buffer << "\n";
    }
    // The program never reached this point.
    cout << "socket closed\n";
    co_return;
}

asio::awaitable<void> accept_connection()
{
    auto ex = co_await asio::this_coro::executor;
    boost::asio::ip::tcp::acceptor acceptor(ex, {{}, 8088});

    tcp::socket sock = co_await acceptor.async_accept(asio::use_awaitable);
    while (true)
    {
        co_spawn(ex, handle_connection(std::move(sock)), asio::detached);
        sock = co_await acceptor.async_accept(asio::use_awaitable);
    }

    co_return;
}

int main()
{
    asio::io_context io_ctx(2);
    co_spawn(io_ctx, accept_connection(), asio::detached);
    io_ctx.run();
}
