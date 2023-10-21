#include <asio.hpp>
#include <iostream>
#include <sstream>

asio::io_context ctx;
asio::ip::tcp::socket sock(ctx);
asio::streambuf response;

void send_data();
void receive_handler(const asio::error_code &ec, std::size_t bytes_transferred);
void send_handler(const asio::error_code &ec, std::size_t bytes_transferred);

void send_handler(const asio::error_code &ec, std::size_t bytes_transferred)
{
    // TODO: Add error checking
    std::cout << ec.message() << ", " << bytes_transferred << " bytes transferred. waiting for response..." << std::endl;
    asio::async_read_until(sock, response, "\n", receive_handler);
    // sock.async_receive(response, 0, receive_handler);
    // asio::buffer buf;
    // sock.async_receive(asio::buffer(buf), 0, receive_handler);
}

void receive_handler(const asio::error_code &ec, std::size_t bytes_transferred)
{
    std::istream is(&response);
    std::string line;
    std::getline(is, line);
    std::cout << ec.message() << ": " << line << std::endl;
    // std::ostringstream os;
    // os << &response;
    // std::string res = os.str();

    // // std::string rx_msg = std::istream(&response).rdbuf();
    // std::cout << ec.message() << ", " << res << std::endl;

    response.consume(bytes_transferred);
    if (line != "quit")
    {
        send_data();
    }
    else
    {
        ctx.stop();
    }
}

void send_data()
{
    using namespace std::chrono_literals;
    static int counter{};
    static std::string msg; // = "sending message-" + std::to_string(++counter) + "\n";
    msg = "sending message-" + std::to_string(++counter) + "\n";
    asio::async_write(sock, asio::buffer(msg, msg.size()), send_handler);

    // sock.async_send(asio::buffer(msg.data(), msg.size()), send_handler);
    // while (counter < 20)
    // {
    //     std::string msg = "sending message-" + std::to_string(++counter) + "\n";
    //     socket.async_send(asio::buffer(msg.data(), msg.size()), send_handler);
    //     std::this_thread::sleep_for(1s);
    // }
}

int main(int argc, char *argv[])
{
    // asio::io_context ctx;
    // asio::ip::tcp::socket socket(ctx);
    asio::ip::address address = asio::ip::make_address("127.0.0.1");
    asio::ip::tcp::endpoint endpoint(address, 8801);
    using work_gurad_type = asio::executor_work_guard<asio::io_context::executor_type>;
    work_gurad_type worker = work_gurad_type(ctx.get_executor());

    std::thread t([&]
                  { ctx.run(); });
    asio::error_code ec;
    sock.connect(endpoint, ec);
    if (!ec)
    {
        std::cout << ec.message() << ", connect to server." << std::endl;
        send_data();
    }
    else
    {
        std::cerr << "Unable to connect to server." << std::endl;
    }
    t.join();
}
