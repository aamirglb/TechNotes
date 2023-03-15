#include <asio.hpp>
#include <iostream>

int main(int argc, char *argv[])
{
    asio::io_context io_ctx;
    asio::ip::tcp::socket socket(io_ctx);
    asio::error_code ec;

    socket.connect(asio::ip::tcp::endpoint(asio::ip::address::from_string("127.0.0.1"), 26401), ec);
    if (ec)
    {
        std::cout << "failed to connected to socket: " << ec.message() << std::endl;
    }
    const std::string message = "Hello from client!!\n";

    // asio::write(socket, asio::buffer(message), ec);

    // if (!ec)
    // {
    //     std::cout << "Client sent hello message!!" << std::endl;
    // }
    // else
    // {
    //     std::cout << "send failed: " << ec.message() << std::endl;
    // }

    asio::streambuf receive_buf;
    // asio::read(socket, receive_buf, asio::transfer_all(), ec);
    asio::read(socket, receive_buf, asio::transfer_exactly(20), ec);
    if (ec && ec != asio::error::eof)
    {
        std::cout << "Received failed: " << ec.message() << std::endl;
    }
    else
    {
        std::cout << "received data..." << std::endl;
        // const char *data = asio::buffer_cast<const char *>(receive_buf.data());
        // std::cout << data << std::endl;
    }
}