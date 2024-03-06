
#include <asio.hpp>
#include <chrono>
#include <thread>
#include <iostream>
#include <vector>
#include <random>
#include <mutex>

std::mutex stream_mutex;

using namespace std::chrono_literals;
using namespace std::placeholders;

void WorkThread(std::shared_ptr<asio::io_context> ioc, int id)
{
    {
        std::scoped_lock<std::mutex> lock(stream_mutex);
        std::cout << "Thread [" << std::this_thread::get_id() << "] started\n";
    }

    while (true)
    {
        try
        {
            asio::error_code ec;
            ioc->run(ec);

            if (ec)
            {
                std::scoped_lock<std::mutex> lock(stream_mutex);
                std::cout << "Thread [" << std::this_thread::get_id() << "] Error: " << ec << "\n";
            }
            break;
        }
        catch (const std::exception &e)
        {
            std::scoped_lock<std::mutex> lock(stream_mutex);
            std::cout << "Thread [" << std::this_thread::get_id() << "] Exception: " << e.what() << "\n";
        }
    }

    {
        std::scoped_lock<std::mutex> lock(stream_mutex);
        std::cout << "Thread [" << std::this_thread::get_id() << "] Finished\n";
    }
}

void TimerHandler(const asio::error_code &ec)
{
    if (ec)
    {
        std::scoped_lock<std::mutex> lock(stream_mutex);
        std::cout << "Thread [" << std::this_thread::get_id() << "] Error: " << ec << "\n";
    }
    else
    {
        std::scoped_lock<std::mutex> lock(stream_mutex);
        std::cout << "Thread [" << std::this_thread::get_id() << "] TimerHandler  " << ec << "\n";
    }
}

// The deadline_timer interface depends on the boost.date_time library and so
// can't be supported by Asio's standalone configuration.
// The basic_waitable_timer<> class is also available in Boost.Asio and so may
// be used with both the Boost and standalone variants.

int main()
{
    std::cout << "main thread [" << std::this_thread::get_id() << "] started" << std::endl;
    auto ioc = std::make_shared<asio::io_context>();
    auto work = std::make_shared<asio::io_context::work>(*ioc);

    {
        std::scoped_lock<std::mutex> lock(stream_mutex);
        std::cout << "Press [Return] to exit." << std::endl;
    }

    std::vector<std::jthread> worker_threads;
    for (int i = 0; i < 2; ++i)
    {
        worker_threads.emplace_back(std::bind(WorkThread, ioc, i + 1));
    }

    asio::steady_timer timer(*ioc);
    timer.expires_from_now(5s);
    timer.async_wait(TimerHandler);

    std::cin.get();
    ioc->stop();
}