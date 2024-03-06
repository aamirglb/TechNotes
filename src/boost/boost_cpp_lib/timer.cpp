#include <asio.hpp>
#include <iostream>

using asio::error_code;
using namespace asio;
using namespace std::chrono_literals;
auto now = std::chrono::steady_clock::now;

int main()
{
    io_context ioc;
    steady_timer timer(ioc, 1s);
    int count = 0;

    std::function<void(error_code)> handler;

    auto const start = now();
    handler = [&](error_code ec)
    {
        std::cout << "at " << (now() - start) / 1.0ms
                  << "ms handler: " << ec.message() << std::endl;

        // if(ec.failed()) { return; }
        if (count++ < 30)
        {
            timer.expires_from_now(1s);
            timer.async_wait(handler);
        }
    };

    timer.async_wait(handler);
    ioc.run();
    std::cout << "at " << (now() - start) / 1.0ms << " Done\n";
}