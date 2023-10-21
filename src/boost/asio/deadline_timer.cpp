#include <asio.hpp>
#include <asio/deadline_timer.hpp>

#include <string>
#include <thread>
#include <chrono>
#include <iostream>

#include <fmt/core.h>
#include <fmt/chrono.h>
#include <fmt/format.h>
#include <fmt/std.h>

void timer_expired(std::string id)
{
    using namespace std::chrono_literals;
    // std::cout << "thread-id = " << std::this_thread::get_id();
    std::cout << fmt::format("thread-id = {} - {:%Y-%m-%d %H:%M:%S} - {} entered.", std::this_thread::get_id(), std::chrono::system_clock::now(), id) << std::endl;
    std::this_thread::sleep_for(5s);

    // std::cout << "thread-id = " << std::this_thread::get_id();
    std::cout << fmt::format(" thread-id = {} - {:%Y-%m-%d %H:%M:%S} - {} leave.", std::this_thread::get_id(), std::chrono::system_clock::now(), id) << std::endl;
}

int main()
{
    asio::io_context context;

    using namespace std::chrono_literals;
    asio::steady_timer timer1(context, std::chrono::steady_clock::now() + 3s);
    asio::steady_timer timer2(context, std::chrono::steady_clock::now() + 3s);

    timer1.async_wait([](auto... vn)
                      { timer_expired("timer-1"); });
    timer2.async_wait([](auto... vn)
                      { timer_expired("timer-2"); });

    std::jthread butler([&]
                        { context.run(); });
    std::cout << "main thread id = " << std::this_thread::get_id() << std::endl;
    context.run();
    // timer1.expires_from_now(5s);
    // timer2.expires_from_now(5s);
}