#include <asio.hpp>
#include <iostream>
#include <fmt/core.h>

struct Session
{
    std::shared_ptr<asio::ip::tcp::socket> socket;
    std::unique_ptr<char[]> buf;
    std::size_t total_bytes_read;
    unsigned int buf_size;
    std::vector<char> msg;
};

void read_handler(const asio::error_code &ec, std::size_t bytes_transferred, std::shared_ptr<Session> session)
{
    if (ec.value() != 0)
    {
        std::cout << fmt::format("Error: {}, {}", ec.value(), ec.message()) << std::endl;
        return;
    }
    session->total_bytes_read += bytes_transferred;
    if (session->total_bytes_read == session->buf_size)
    {
        std::copy(session->buf.get(), session->buf.get() + 7, std::back_inserter(session->msg));
        std::replace(session->msg.begin(), session->msg.end(), '\n', ' ');
        auto last = std::unique(session->msg.begin(), session->msg.end(), [](char c, char d)
                                { return c == ' ' && d == ' '; });
        session->msg.erase(last, session->msg.end());

        for (const char &ch : session->msg)
        {
            std::cout << ch;
        }
        std::cout << std::endl;
        // std::cout << fmt::format("Bytes read: {}, message: {}", bytes_transferred, session->buf.get()) << std::endl;
        session->total_bytes_read = 0;
        // return;
    }
    session->socket->async_read_some(asio::buffer(session->buf.get() + session->total_bytes_read,
                                                  session->buf_size - session->total_bytes_read),
                                     std::bind(read_handler, std::placeholders::_1, std::placeholders::_2, session));
}

void read_from_socket(std::shared_ptr<asio::ip::tcp::socket> socket)
{
    auto session = std::make_shared<Session>();
    const unsigned int MESSAGE_SIZE{7};
    session->buf.reset(new char[MESSAGE_SIZE + 1]);
    session->buf.get()[MESSAGE_SIZE] = 0;
    session->socket = socket;
    session->buf_size = MESSAGE_SIZE;

    session->socket->async_read_some(asio::buffer(session->buf.get(), session->buf_size),
                                     std::bind(read_handler, std::placeholders::_1, std::placeholders::_2, session));
}

int main()
{
    std::string local_addr{"127.0.0.1"};
    std::uint16_t port{3333};
    try
    {
        asio::ip::tcp::endpoint endpoint{asio::ip::address::from_string(local_addr), port};
        asio::io_context io_ctx;
        auto socket = std::make_shared<asio::ip::tcp::socket>(io_ctx, endpoint.protocol());
        socket->connect(endpoint);
        read_from_socket(socket);
        io_ctx.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}