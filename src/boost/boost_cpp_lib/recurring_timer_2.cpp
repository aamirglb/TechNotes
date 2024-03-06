
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

void TimerHandler(
    const asio::error_code &ec,
    std::shared_ptr<asio::steady_timer> timer,
    std::shared_ptr<asio::io_context::strand> strand)
{
    if (ec)
    {
        std::scoped_lock<std::mutex> lock(stream_mutex);
        std::cout << "Thread [" << std::this_thread::get_id() << "] Error: " << ec << "\n";
    }
    else
    {
        {
            std::scoped_lock<std::mutex> lock(stream_mutex);
            std::cout << "Thread [" << std::this_thread::get_id() << "] TimerHandler  " << ec << "\n";
        }
        timer->expires_from_now(1s);
        timer->async_wait(std::bind(&TimerHandler, _1, timer, strand));
    }
}

void PrintNum(int x)
{
    std::cout << "[" << std::this_thread::get_id() << "] x: " << x << std::endl;
    std::this_thread::sleep_for(1s);
}

int main()
{
    std::cout << "main thread [" << std::this_thread::get_id() << "] started" << std::endl;
    auto ioc = std::make_shared<asio::io_context>();
    auto work = std::make_shared<asio::io_context::work>(*ioc);
    auto strand = std::make_shared<asio::io_context::strand>(*ioc);

    {
        std::scoped_lock<std::mutex> lock(stream_mutex);
        std::cout << "Press [Return] to exit." << std::endl;
    }

    std::vector<std::jthread> worker_threads;
    for (int i = 0; i < 2; ++i)
    {
        worker_threads.emplace_back(std::bind(WorkThread, ioc, i + 1));
    }

    std::this_thread::sleep_for(1s);
    int x = 0;
    strand->post(std::bind(&PrintNum, ++x));
    strand->post(std::bind(&PrintNum, ++x));
    strand->post(std::bind(&PrintNum, ++x));
    strand->post(std::bind(&PrintNum, ++x));
    strand->post(std::bind(&PrintNum, ++x));
    strand->post(std::bind(&PrintNum, ++x));

    std::shared_ptr<asio::steady_timer> timer = std::make_shared<asio::steady_timer>(*ioc);
    timer->expires_from_now(1s);
    timer->async_wait(strand->wrap(std::bind(&TimerHandler, _1, timer, strand)));

    std::cin.get();
    ioc->stop();
}