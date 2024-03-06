#include <asio.hpp>
#include <chrono>
#include <thread>
#include <iostream>
#include <vector>
#include <random>

asio::io_context ioc;
std::unordered_map<std::thread::id, int> thread_ids;

using namespace std::chrono_literals;

void WorkThread(int id)
{
    std::cout << "Thread started\n";
    thread_ids[std::this_thread::get_id()] = id;
    ioc.run();
    std::cout << "Thread Finished\n";
}

void OnTimeout(const asio::error_code &ec)
{
    if (!ec)
    {
        std::cout << "Handler completed by thread " << thread_ids[std::this_thread::get_id()] << std::endl;
    }
}

// The stop function will signal the io_context that all work should be stopped.
int main()
{
    auto work = std::make_shared<asio::io_context::work>(ioc);
    std::cout << "Press [Return] to exit." << std::endl;

    std::vector<std::jthread> worker_threads;
    for (int i = 0; i < 4; ++i)
    {
        worker_threads.emplace_back(std::bind(WorkThread, i + 1));
    }
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution dist(5, 8);

    std::vector<std::shared_ptr<asio::steady_timer>> timers;
    for (int i = 0; i < 10; ++i)
    {
        auto t = dist(rng);
        timers.emplace_back(std::make_shared<asio::steady_timer>(ioc, std::chrono::seconds(t)));
        timers.back()->async_wait(OnTimeout);
    }
    std::cin.get();
    ioc.stop();
}