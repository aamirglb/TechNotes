#include <asio.hpp>
#include <iostream>

void write_to_socket(asio::ip::tcp::socket &s, const std::string msg = "Hello World!!")
{
    std::size_t total_bytes_written{};

    while (total_bytes_written != msg.length())
    {
        total_bytes_written += s.write_some(
            asio::buffer(msg.c_str() + total_bytes_written, msg.length() - total_bytes_written));
    }
}

int main(int argc, char *argv[])
{
    std::string server_ip{"127.0.0.1"};
    std::uint16_t port{3333};
    asio::ip::tcp::endpoint endpoint{asio::ip::address::from_string(server_ip), port};
    asio::io_context io_ctx;
    asio::ip::tcp::socket s(io_ctx, endpoint.protocol());
    s.connect(endpoint);

    if (argc > 1)
    {
        write_to_socket(s, argv[1]);
    }
    else
    {
        write_to_socket(s);
    }
}
