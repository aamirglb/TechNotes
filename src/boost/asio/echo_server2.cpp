#include <asio.hpp>
#include <string>
#include <iostream>
#include <array>
#include <functional>
#include <thread>

#include <fmt/core.h>
#include <fmt/chrono.h>
#include <fmt/format.h>
#include <fmt/std.h>
#include <fmt/color.h>

using namespace std::chrono_literals;
const auto TIMEOUT{5s};
auto now = std::chrono::system_clock::now;

void dump_message(const char *ptr, size_t sz)
{
    for (int i = 0; i < sz; ++i)
    {
        std::cout << std::setw(2) << std::setfill('0') << static_cast<int>(ptr[i] & 0xFF) << ' ';
    }
    std::cout << std::endl;
}

int main(int argc, char *argv[])
{
    std::uint16_t port{15001};
    if (argc > 1)
    {
        try
        {
            port = std::stoi(argv[1]);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    asio::io_context ctx;
    asio::ip::udp::endpoint receiver(asio::ip::udp::v4(), port);
    asio::ip::udp::socket socket(ctx, receiver);
    asio::steady_timer timer(ctx, TIMEOUT);

    std::function<void(asio::error_code)> handler;
    int count{};

    handler = [&](std::error_code ec)
    {
        if (ec != asio::error::operation_aborted)
        {
            fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
                       "{:%Y-%m-%d %H:%M:%S} timeout, no message received {}", std::chrono::system_clock::now(), count++);
            std::cout << std::endl;
            timer.expires_after(TIMEOUT);
            timer.async_wait(handler);
        }
        else
        {
            std::cout << "*** operation aborted. ***" << std::endl;
        }
    };

    timer.async_wait(handler);
    std::jthread t([&]
                   { ctx.run(); });

    for (;;)
    {
        std::array<char, 65536> buffer;
        asio::ip::udp::endpoint sender;
        std::size_t bytes_received = socket.receive_from(asio::mutable_buffer(buffer.data(), buffer.size()), sender);

        // cancels any pending asynchronous waits, and get number of asynchronous waits that were cancelled
        if (timer.expires_after(TIMEOUT) > 0)
        {
            // start new async timer
            timer.async_wait(handler);
        }

        std::string msg(std::begin(buffer), std::begin(buffer) + (bytes_received - 1));
        fmt::print(fg(fmt::color::cyan), "{:%Y-%m-%d %H:%M:%S}: {}", now(), msg);
        std::cout << msg << std::endl;
        dump_message(buffer.data(), bytes_received);
        socket.send_to(asio::mutable_buffer(buffer.data(), bytes_received), sender);

        if (msg == "quit")
        {
            char bye_msg[] = "good bye";

            socket.send_to(asio::buffer(bye_msg), sender);
            break;
        }
    }
    ctx.stop();
    std::cout << "Done." << std::endl;
}