#include <ctime>
#include <iostream>
#include <string>
#include <memory>
#include <asio.hpp>

using asio::ip::tcp;

std::string make_daytime_string() {
    std::time_t now = std::time(0);
    return std::ctime(&now);
}

class tcp_connectoin;

// tcp connectoin class
class tcp_connection : public std::enable_shared_from_this<tcp_connection> {
public:
    // using pointer = std::shared_ptr<tcp_connectoin>;
    typedef std::shared_ptr<tcp_connection> pointer;

    static pointer create(asio::io_context& io) {
        return std::shared_ptr<tcp_connection>(new tcp_connection(io));
        // return std::make_shared<tcp_connection>(io);
        // return pointer(new tcp_connection(io));
    }

    tcp::socket& socket() {
        return socket_;
    }

    void start() {
        message_ = make_daytime_string();

        asio::async_write(socket_, asio::buffer(message_),
            std::bind(&tcp_connection::handle_write, shared_from_this(),
              std::placeholders::_1,
              std::placeholders::_2));
    }
private:
    tcp_connection(asio::io_context& io)
    : socket_(io)
    {}

    void handle_write(const asio::error_code& /*error*/,
        size_t /*bytes_transferred*/)
    {
        std::cout << "async_write completed." << std::endl;
    }

    tcp::socket socket_;
    std::string message_;
};


// tcp_server class
class tcp_server {
public:
    tcp_server(asio::io_context& io)
        : io_{io}
        , acceptor_(io, tcp::endpoint(tcp::v4(), 13))
    {
        start_accept();
    }
private:
    void start_accept() {
        tcp_connection::pointer new_connection = tcp_connection::create(io_);
        acceptor_.async_accept(new_connection->socket(),
            std::bind(&tcp_server::handle_accept, this, new_connection,
             std::placeholders::_1));
    }

    void handle_accept(tcp_connection::pointer new_connectoin,
        const asio::error_code& error) {
        if(!error) {
            new_connectoin->start();
        }
        start_accept();
    }

    asio::io_context& io_;
    tcp::acceptor acceptor_;
};

int main() {
    try {
        asio::io_context io;
        tcp_server server(io);
        io.run();
    } catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
