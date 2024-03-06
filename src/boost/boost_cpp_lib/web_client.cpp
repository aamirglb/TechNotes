#include <asio.hpp>
#include <array>
#include <string>
#include <iostream>
#include <cstdint>

using namespace asio;
using namespace asio::ip;

io_context ioc;
tcp::resolver resolv{ioc};
tcp::socket tcp_socket{ioc};
std::array<char, 4096 * 2> bytes;

void read_handler(const error_code &ec, std::size_t bytes_transferred)
{
    if (!ec)
    {
        std::cout.write(static_cast<const char *>(bytes.data()), bytes_transferred);
        tcp_socket.async_read_some(buffer(bytes), read_handler);
    }
}

void connect_handler(const error_code &ec)
{
    if (!ec)
    {
        std::string r =
            // "GET / HTTP/1.1\r\nHost: theboostcpplibraries.com\r\n\r\n";
            "GET /api/media HTTP/1.1\r\nHost: localhost\r\n\r\n";
        write(tcp_socket, buffer(r));
        tcp_socket.async_read_some(buffer(bytes), read_handler);
    }
}

void resolve_handler(const error_code &ec, tcp::resolver::iterator it)
{
    if (!ec)
    {
        tcp_socket.async_connect(*it, connect_handler);
    }
}

int main()
{
    tcp::resolver::query q{"localhost", "3000"};
    resolv.async_resolve(q, resolve_handler);
    ioc.run();
}