#include <asio.hpp>
#include <iostream>

using namespace std::placeholders;

class application
{
public:
    application(asio::io_context &ctx, const std::string &hostname)
        : resolver(ctx), socket(ctx)
    {
        request = "GET / HTTP/1.1\n"
                  "Host: " +
                  hostname + "\n"
                             "Connection: close\n\n";

        resolver.async_resolve(hostname, "http", std::bind(&application::on_resolve, this, _1, _2));
    }

private:
    void on_resolve(asio::error_code ec, asio::ip::tcp::resolver::results_type results)
    {
        std::cout << "Resolve: " << ec.message() << std::endl;
        asio::async_connect(socket, results, std::bind(&application::on_connect, this, _1, _2));
    }

    void on_connect(asio::error_code ec, const asio::ip::tcp::endpoint &endpoint)
    {
        std::cout << "Connect: " << ec.message() << ", endpoint: " << endpoint << std::endl;
        asio::async_write(socket, asio::buffer(request), std::bind(&application::on_write, this, _1, _2));
    }

    void on_write(asio::error_code ec, std::size_t bytes_transferred)
    {
        std::cout << "Write: " << ec.message() << ", bytes transferred: " << bytes_transferred << std::endl;
        asio::async_read(socket, response, std::bind(&application::on_read, this, _1, _2));
    }

    void on_read(asio::error_code ec, std::size_t bytes_transferred)
    {
        std::cout << "Read: " << ec.message() << ", bytes transferred: " << bytes_transferred << "\n\n"
                  << std::istream(&response).rdbuf() << std::endl;
    }
    asio::ip::tcp::resolver resolver;
    asio::ip::tcp::socket socket;
    std::string request;
    asio::streambuf response;
};

int main(int argc, char *argv[])
{
    asio::io_context ctx;
    application app(ctx, argv[1]);
    ctx.run();
}