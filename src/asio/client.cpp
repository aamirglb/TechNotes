#include <iostream>
#include <chrono>
#include <cstdint>
#include <asio.hpp>

using asio::ip::tcp;
using namespace std::chrono_literals;

class MessageSender
{
public:
    MessageSender(asio::io_context& ioc, tcp::socket& sock, int32_t msg_count = 60)
    : timer_{ioc, 200ms}
    , socket_{sock}
    , count_{0}
    , stop_count_{msg_count}
    , message_{"hello world - "}
    {
        timer_.async_wait(std::bind(&MessageSender::SendMessage, this));
    }

    ~MessageSender()
    {
        std::cout << stop_count_ << " messages sent to the server." << std::endl;
    }

    void SendMessage()
    {
        if(count_ < stop_count_)
        {
            message_ += std::format("{}\n", count_);
            count_ += 1;
            auto result = asio::write(socket_, asio::buffer(message_));
            // std::cout << "[MessageSender]: " << count_ << ": " << message_ << std::endl;
            std::cout << "[MessageSender]: " << "data sent: " << message_.length() << '/' << result << std::endl;
            message_.pop_back();

            timer_.expires_at(timer_.expiry() + 200ms);
            timer_.async_wait(std::bind(&MessageSender::SendMessage, this));
        }
    }
private:
    asio::steady_timer timer_;
    tcp::socket& socket_;
    int32_t count_;
    int32_t stop_count_;
    std::string message_;
};

int main(int argc, char* argv[])
{
    using asio::ip::tcp;
    asio::io_context ioc;

    tcp::socket socket(ioc);
    tcp::resolver resolver(ioc);

    asio::connect(socket, resolver.resolve("127.0.0.1", "25000"));
    MessageSender sender(ioc, socket);

    ioc.run();

    // std::string data{"hello from client..."};
    // auto result = asio::write(socket, asio::buffer(data));
    // std::cout << "data sent: " << data.length() << '/' << result << std::endl;

    // std::error_code ec;
    // socket.shutdown(asio::ip::tcp::socket::shutdown_both, ec);
    // socket.close();
    return 0;
}