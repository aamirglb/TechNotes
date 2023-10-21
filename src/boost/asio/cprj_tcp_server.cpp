#include <asio.hpp>
#include <iostream>

std::string read_(asio::ip::tcp::socket &socket)
{
    asio::streambuf buf;
    asio::read_until(socket, buf, "\n");
    std::string data = asio::buffer_cast<const char *>(buf.data());
    return data;
}

void send_(asio::ip::tcp::socket &socket, const std::string &message)
{
    const std::string msg = message + "\n";
    asio::write(socket, asio::buffer(message));
}

int main(int argc, char *argv[])
{
    asio::io_context io_ctx;
    asio::ip::tcp::acceptor acceptor_(io_ctx, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 11221));
    asio::ip::tcp::socket socket_(io_ctx);
    acceptor_.accept(socket_);
    std::string message = read_(socket_);
    std::cout << message << std::endl;
    send_(socket_, "Hello from server!!");
    std::cout << "message sent to client" << std::endl;
}