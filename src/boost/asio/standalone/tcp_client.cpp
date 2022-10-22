#include <chrono>
#include <fstream>
#include <iostream>
#include <list>
#include <asio.hpp>
using namespace std::chrono_literals;

namespace tcpsocket {

    using asio::ip::tcp;
    using asio::error_code;
    // using system::error_code;

    class client {
      public:
        client(asio::any_io_executor ex) : socket_(ex) {}

        size_t bytes_received() const { return bytes_received_; }
        std::string get_data() const { return std::string(data.begin(), data.end()); }

        void connect(const std::string& host, const std::string& port) {
            post(socket_.get_executor(), [=, this] { do_connect(host, port); });
        }
        void write(std::string msg) {
            post(socket_.get_executor(), [=, this] { do_write(msg); });
        }
        void read() {
            post(socket_.get_executor(), [=, this] { do_read(); });
        }

      private:
        void do_connect(const std::string& host, const std::string& port) {
            if (host.empty() || port.empty())
                return;

            tcp::resolver resolver{socket_.get_executor()};

            async_connect(socket_, resolver.resolve(host, port),
                          [this](error_code ec, tcp::endpoint /*endpoint*/) {
                              if (!ec)
                                  do_read();
                              else
                                  std::cerr << ec.message() << std::endl;
                          });
        }

        void do_write(const std::string& msg) {
            error_code ec;
            asio::write(socket_, asio::buffer(msg), ec);
            if (ec) {
                std::cerr << "Closing (" << ec.message() << ")" << std::endl;
                return socket_.close();
            }
        }

        void do_read() {
            socket_.async_read_some( //
                asio::buffer(data),
                [this](error_code ec, std::size_t bytes) {
                    if (ec)
                        return socket_.close();
                    bytes_received_ += bytes;
                    do_read();
                });
        }

        std::atomic_size_t             bytes_received_{0};
        std::array<unsigned char, 128> data;
        tcp::socket                    socket_;
    };

} // namespace tcpsocket

struct Cfg {
    unsigned id{};
    std::string host;
    std::string port;
};

struct Client {
    Client(unsigned id, asio::any_io_executor ex) : id_(id), impl_(ex) {}

    unsigned          id_;
    tcpsocket::client impl_;
};

int main()
{
    asio::io_context ioc;

    std::list<Client> clients;

    std::vector<Cfg> const config{
        {125u, "127.0.0.1", "30000"},
        {137u, "127.0.0.1", "30001"},
        // {149u, "127.0.0.1", "30002"},
        // {161u, "127.0.0.1", "30003"},
        // {173u, "127.0.0.1", "30004"},
        // {185u, "127.0.0.1", "30005"},
        // {197u, "127.0.0.1", "30006"},
        // {209u, "127.0.0.1", "30007"},
        // {221u, "127.0.0.1", "30008"},
        // {233u, "127.0.0.1", "30009"},
        // {245u, "127.0.0.1", "30010"},
    };

    for (auto& [id, host, port] : config) {
        auto& c = clients.emplace_back(id, make_strand(ioc));

        c.impl_.connect(host, port);
        c.impl_.write(std::to_string(id) + " connected to " + host + ":" + port + "\n");
    }

    ioc.run_for(150ms);

    for (auto& [id, impl]: clients)
        std::cout << id << " received " << impl.bytes_received() << ": " << impl.get_data() << "\n";
}

// (for a in {30000..30010}; do netcat -tlp $a < main.cpp & done)