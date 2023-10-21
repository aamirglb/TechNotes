#include <asio.hpp>
#include <iostream>
#include <fmt/core.h>

struct Session
{
    std::shared_ptr<asio::ip::tcp::socket> socket;
    std::unique_ptr<char[]> buf;
    std::vector<std::string> all_msgs;
    int msg_length{};
};

enum CycleType
{
    eHeader,
    eMessage,
};

CycleType curr_cycle{eHeader};

void read_handler(const asio::error_code &ec, std::size_t bytes_transferred, std::shared_ptr<Session> session)
{
    if (ec.value() != 0)
    {
        std::cout << fmt::format("Error: {}, {}", ec.value(), ec.message()) << std::endl;
        return;
    }

    // received message header
    // if (bytes_transferred == 4)
    if (curr_cycle == eHeader)
    {
        curr_cycle = eMessage;
        std::cout << "raw length: " << session->buf.get() << std::endl;
        session->msg_length = std::stoi(session->buf.get());
        std::cout << fmt::format("Message Length: {}", session->msg_length) << std::endl;

        session->buf.reset(new char[session->msg_length + 1]);
    }
    else
    {
        curr_cycle = eHeader;
        // if (bytes_transferred == session->msg_length + 1)
        {
            session->buf.get()[session->msg_length] = 0;
            std::cout << "message: " << session->buf.get() << std::endl;
            session->all_msgs.emplace_back(session->buf.get());

            if (session->all_msgs.back() == "quit")
            {
                for (int i = 0; const auto &msg : session->all_msgs)
                {
                    std::cout << ++i << ": " << msg << std::endl;
                }
                return;
            }

            session->buf.reset(new char[3 + 1]);
            session->buf.get()[3] = 0;
            session->msg_length = 3;
        }
    }

    asio::async_read(*session->socket.get(), asio::buffer(session->buf.get(), session->msg_length + 1),
                     std::bind(read_handler, std::placeholders::_1, std::placeholders::_2, session));
}

void read_from_socket(std::shared_ptr<asio::ip::tcp::socket> socket)
{
    auto session = std::make_shared<Session>();
    const unsigned int HEADER_SIZE{3};
    session->buf.reset(new char[HEADER_SIZE + 1]);
    session->buf.get()[HEADER_SIZE] = 0;
    session->socket = socket;

    asio::async_read(*session->socket.get(), asio::buffer(session->buf.get(), HEADER_SIZE + 1),
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