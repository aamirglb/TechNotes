#include <asio.hpp>
#include <vector>
#include <thread>
#include <memory>
#include <deque>

class chat_handler : public std::enabled_shared_from_this<chat_handler>
{
public:
    chat_handler(asio::io_context &context)
        : context_(context), socket_(context), write_strand_(context)
    {
    }

    asio::ip::tcp::socket &socket()
    {
        return socket_;
    }

    void start()
    {
        read_pakcet();
    }

private:
    asio::io_context &context_;
    asio::ip::tcp::socket socket_;
    asio::io_context::strand write_strand_;
    asio::streambuf in_packet_;
    std::deque<std::string> send_pakcet_queue;
};

template <typename ConnectionHandler>
class asio_generic_server
{
    using shared_handler_t = std::shared_ptr<ConnectionHandler>;

public:
    asio_generic_server(int thread_count = 1)
        : thread_count_{thread_count}, acceptor_{io_context_}
    {
    }

    void start_server(uint16_t port)
    {
        auto handler = std::make_shared<ConnectionHandler>(io_contex_);

        asio::ip::tcp::endpoint endpoint(asio::io::tcp::v4(), port);
        acceptor_.open(endpoint.protocol());
        acceptor_.set_option(tcp::acceptor::reuse_address(true));
        acceptor_.bind(endpoint);
        acceptor_.listen();

        acceptor_.async_accept(handler->socket(), [=](auto ec)
                               { handle_new_connecton(handler, ec); });

        for (int i = 0; i < thread_count_; ++i)
        {
            thread_pool_.emplace_back([=]
                                      { io_context_.run(); });
        }
    }

private:
    void handle_new_connecton(shared_handler_t handler, const system::error_code &error)
    {
        if (error)
            return;

        handler->start();
        auto new_handler = std::make_shared<ConnectionHandler>(io_context_);
        acceptor_.async_accept(new_handler->socket(), [=](auto ec)
                               { handler_new_connection(new_handler, ec); });
    }

    int thread_count_;
    std::vector<std::thread> thread_pool_;
    asio::io_context io_context_;
    asio::ip::tcp::acceptor acceptor_;
};