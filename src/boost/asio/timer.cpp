#include <asio.hpp>
#include <functional>
#include <fmt/core.h>
#include <fmt/std.h>
#include <iostream>

using namespace std::chrono_literals;

int main()
{
    asio::io_context ctx;
    asio::steady_timer t(ctx, 1s);
    int count{};

    std::function<void(asio::error_code)> handler;
    auto const start = std::chrono::steady_clock::now();
    handler = [&](asio::error_code ec)
    {
        std::cout << "at " << (std::chrono::steady_clock::now() - start) / 1.0ms << " ms handler: " << ec.message() << std::endl;
        // if (ec.failed())
        //     return;

        if (count++ < 20)
        {
            t.expires_from_now(1s);
            t.async_wait(handler);
        }
    };

    t.async_wait(handler);
    ctx.run();
    std::cout << "at " << (std::chrono::steady_clock::now() - start) / 1.0ms << " Done" << std::endl;
}