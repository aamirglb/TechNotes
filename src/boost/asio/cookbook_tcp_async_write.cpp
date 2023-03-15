#include <asio.hpp>
#include <iostream>
#include <memory>

struct Session
{
    std::shared_ptr<asio::ip::tcp::socket> socket;
    std::string buf;
    std::size_t total_bytes_written;
    asio::streambuf streambuf;
};

void write_handler(const asio::error_code &ec, std::size_t bytes_transferred, std::shared_ptr<Session> session)
{
    if (ec.value() != 0)
    {
        std::cout << "Error occured!! Error code: " << ec.value() << ", " << ec.message() << std::endl;
        return;
    }
    session->total_bytes_written += bytes_transferred;
    if (session->total_bytes_written == session->buf.length())
    {
        // session->socket->async_receive(session->streambuf, '\n', [](auto... vn) {});
        return;
    }

    session->socket->async_write_some(
        asio::buffer(session->buf.c_str() + session->total_bytes_written,
                     session->buf.length() - session->total_bytes_written),
        std::bind(write_handler, std::placeholders::_1, std::placeholders::_2, session));

    //
}

void write_to_socket(std::shared_ptr<asio::ip::tcp::socket> socket)
{
    std::shared_ptr<Session> session = std::make_shared<Session>();
    session->buf = std::string("Hello World!!");
    session->total_bytes_written = 0;
    session->socket = socket;

    session->socket->async_write_some(
        asio::buffer(session->buf),
        std::bind(write_handler, std::placeholders::_1, std::placeholders::_2, session));
}

int main()
{
    std::string server_ip{"127.0.0.1"};
    std::uint16_t port{3333};

    asio::error_code ec;
    asio::io_context io_ctx;

    try
    {
        asio::ip::tcp::endpoint endpoint{asio::ip::address::from_string(server_ip), port};

        auto sock = std::make_shared<asio::ip::tcp::socket>(io_ctx, endpoint.protocol());
        sock->connect(endpoint);
        write_to_socket(sock);
        io_ctx.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}