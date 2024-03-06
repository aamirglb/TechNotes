#include <asio.hpp>
#include <asio/steady_timer.hpp>
#include <chrono>
#include <iostream>
#include <thread>

using namespace asio;
using namespace std::chrono_literals;

int main()
{
    asio::io_context ioc;
    asio::steady_timer timer{ioc, 3s};
    timer.async_wait([&t = timer](const error_code &ec)
                     { std::cout << "3 seconds elapsed\n";
                     std::cout << "handler id: " << std::this_thread::get_id() << '\n'; });

    std::cout << "main thread id: " << std::this_thread::get_id() << "\n";

    std::jthread t([&]()
                   {
        std::cout << "thread id: " << std::this_thread::get_id() << std::endl;
        ioc.run(); });
    // ioc.run();
    std::this_thread::sleep_for(5s);
    std::cout << "main thread wokeup after 5 second\n";
}