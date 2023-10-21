#include <asio.hpp>
#include <deque>
#include <iomanip>
#include <iostream>

// using boost::system::error_code;
using asio::error_code;
// namespace asio = boost::asio;
using asio::ip::tcp;

class AsyncClient {
  public:
    AsyncClient(asio::io_context& io_context, std::string const& server_address,
                std::string const& server_port)
        : socket_(io_context)
        , resolver_(io_context)
        , server_address_(server_address)
        , server_port_(server_port) {}

    void Start() {
        auto endpoints = resolver_.resolve(server_address_, server_port_);
        asio::async_connect(socket_, endpoints, [&](error_code error, tcp::endpoint const&) {
            if (!error) {
                std::cout << "Connected to server" << std::endl;
                ReadLoop();
            } else {
                std::cerr << "Error while connecting to server: " << error.message() << std::endl;
            }
        });
    }

    void Send(std::string message) {
        post(socket_.get_executor(), [this, m = std::move(message)]() mutable {
            outbox_.push_back(std::move(m));
            if (outbox_.size() == 1)
                DoWriteLoop();
        });
    }

  private: // all private handlers assumed to be on the service thread
    void DoWriteLoop() {
        if (outbox_.empty())
            return;

        async_write(socket_, asio::buffer(outbox_.front()),
                    [&](error_code error, size_t /*bytes_transferred*/) {
                        if (error) {
                            std::cerr << "Error while writing to server: " << error.message() << std::endl;
                        } else {
                            outbox_.pop_front();
                            DoWriteLoop();
                        }
                    });
    }

    void ReadLoop() {
        std::cout << "Buffer: " << quoted(input_buffer_) << std::endl;
        asio::async_read_until(
            socket_, asio::dynamic_buffer(input_buffer_), '\n',
            [&](error_code error, size_t bytes_transferred) {
                if (error) {
                    if (error == asio::error::eof) {
                        std::cout << "Connection closed by peer" << std::endl;
                    } else {
                        std::cerr << "Error: " << error.message() << " (" << error.value() << " - "
                                  << error.category().name() << ")" << std::endl;
                        return;
                    }
                }

                std::cout << "Received message: " << std::quoted(input_buffer_.substr(0, bytes_transferred)) << std::endl;
                input_buffer_.erase(0, bytes_transferred);

                if (!error)
                    ReadLoop();
            });
    }

    tcp::socket             socket_;
    tcp::resolver           resolver_;
    std::string             server_address_, server_port_, input_buffer_;
    std::deque<std::string> outbox_;
};

void InputLoop(AsyncClient& c) {
    std::string message;
    while (std::getline(std::cin, message)) {
        if (!message.empty())
            c.Send(message + '\n');
    }
}

int main() {
    asio::io_context ioc;
    AsyncClient      c(ioc, "127.0.0.1", "8989");

    c.Start();

    std::thread ui(InputLoop, std::ref(c));

    ioc.run();
    ui.join();
}