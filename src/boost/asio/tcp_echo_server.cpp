#include <iostream>
#include <optional>
#include <fmt/core.h>
#include <optional>
#include <functional>

#include <asio.hpp>

class session : public std::enable_shared_from_this<session>
{
public:
    session(asio::ip::tcp::socket &&socket, int id = 1)
        : socket(std::move(socket)), client_id(id)
    {
    }

    void start()
    {
        char delimiter = '\n';
        std::cout << "client-" << client_id << " started." << std::endl;
        asio::async_read_until(socket,
                               streambuf,
                               delimiter,
                               // clang-format off
                                [self = shared_from_this()](asio::error_code ec, std::size_t bytes_transferred)
                                { 
                                    std::cout << std::istream(&self->streambuf).rdbuf() << std::endl; 
                                    // asio::async_read_until(self->socket, self->streambuf, '\n', [](auto ... vn){});
                                });
                                ; // clang-format on
    }

    ~session()
    {
        std::cout << "client-" << client_id << " finished." << std::endl;
    }

private:
    asio::ip::tcp::socket socket;
    asio::streambuf streambuf;
    int client_id;
    std::function<void(asio::error_code, std::size_t)> session_handler;
};

class server
{
public:
    server(asio::io_context &ctx, std::uint16_t port)
        : ctx(ctx), acceptor(ctx, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
    {
    }

    void async_accept()
    {
        socket.emplace(ctx);

        // clang-format off
        acceptor.async_accept(*socket, [&](asio::error_code ec)
        {
            std::cout << "client-" << ++client_count << " connected." << std::endl;
            std::make_shared<session>(std::move(*socket), client_count)->start();
            async_accept(); 
        });
        // clang-format on
    }

private:
    asio::io_context &ctx;
    asio::ip::tcp::acceptor acceptor;
    std::optional<asio::ip::tcp::socket> socket;
    int client_count{};
};

int main()
{
    asio::io_context ctx;
    server s(ctx, 15001);
    s.async_accept();
    ctx.run();
    std::cout << "Done." << std::endl;
}