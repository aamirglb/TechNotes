#include <asio.hpp>
#include <string>
#include <ctime>

using namespace asio;
using namespace asio::ip;

io_context ioc;
tcp::endpoint tcp_endpoint{tcp::v4(), 2014};
tcp::acceptor tcp_acceptor{ioc, tcp_endpoint};
tcp::socket tcp_socket{ioc};
std::string data;

void write_handler(const error_code &ec, std::size_t bytes_transferred)
{
    if (!ec)
    {
        tcp_socket.shutdown(tcp::socket::shutdown_send);
    }
}

void accept_handler(const error_code &ec)
{
    if (!ec)
    {
        std::time_t now = std::time(nullptr);
        data = std::ctime(&now);
        async_write(tcp_socket, buffer(data), write_handler);
    }
}

int main()
{
    tcp_acceptor.listen();
    tcp_acceptor.async_accept(tcp_socket, accept_handler);
    ioc.run();
}