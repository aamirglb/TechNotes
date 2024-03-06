#include <asio.hpp>
#include <chrono>
#include <thread>
#include <iostream>
#include <vector>
#include <random>
#include <mutex>

std::unordered_map<std::thread::id, int> thread_ids;
std::mutex stream_mutex;

using namespace std::chrono_literals;
using namespace std::placeholders;

void WorkThread(std::shared_ptr<asio::io_context> ioc, int id)
{
    {
        std::scoped_lock<std::mutex> lock(stream_mutex);
        std::cout << "Thread " << id << " started\n";
        thread_ids[std::this_thread::get_id()] = id;
    }
    ioc->run();

    {
        std::scoped_lock<std::mutex> lock(stream_mutex);
        std::cout << "Thread Finished\n";
    }
}

void OnTimeout(const asio::error_code &ec, int timeout)
{
    if (!ec)
    {
        std::cout << "Handler completed by thread " << thread_ids[std::this_thread::get_id()] << " after " << timeout << "s" << std::endl;
    }
}

// The stop function will signal the io_context that all work should be stopped.
int main()
{
    auto ioc = std::make_shared<asio::io_context>();
    auto work = std::make_shared<asio::io_context::work>(*ioc);
    std::cout << "Press [Return] to exit." << std::endl;

    std::vector<std::jthread> worker_threads;
    for (int i = 0; i < 4; ++i)
    {
        worker_threads.emplace_back(std::bind(WorkThread, ioc, i + 1));
    }
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution dist(5, 15);

    std::vector<std::shared_ptr<asio::steady_timer>> timers;
    for (int i = 0; i < 10; ++i)
    {
        auto timeout = 3; // dist(rng);
        std::cout << "timeout set to: " << timeout << std::endl;
        timers.emplace_back(std::make_shared<asio::steady_timer>(*ioc, std::chrono::seconds(timeout)));
        timers.back()->async_wait(std::bind(OnTimeout, _1, timeout));
    }
    std::cin.get();
    ioc->stop();
}