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

// strand object is correctly serializing the event processing to only one
// thread at a time. It is very important that we notice that strand does
// not serialize work through only one thread either
void WorkThread(std::shared_ptr<asio::io_context> ioc, int id)
{
    {
        std::scoped_lock<std::mutex> lock(stream_mutex);
        std::cout << "Thread [" << std::this_thread::get_id() << "] started\n";
        thread_ids[std::this_thread::get_id()] = id;
    }
    ioc->run();

    {
        std::scoped_lock<std::mutex> lock(stream_mutex);
        std::cout << "Thread Finished\n";
    }
}

void PrintNum(int x)
{
    std::cout << "[" << std::this_thread::get_id() << "] x: " << x << std::endl;
}

int main()
{
    std::cout << "main thread [" << std::this_thread::get_id() << "] started" << std::endl;
    auto ioc = std::make_shared<asio::io_context>();
    auto work = std::make_shared<asio::io_context::work>(*ioc);
    asio::io_context::strand strand(*ioc);

    {
        std::scoped_lock<std::mutex> lock(stream_mutex);
        std::cout << "The program will exit when all work has finished." << std::endl;
    }

    std::vector<std::jthread> worker_threads;
    for (int i = 0; i < 4; ++i)
    {
        worker_threads.emplace_back(std::bind(WorkThread, ioc, i + 1));
    }

    std::this_thread::sleep_for(100ms);
    ioc->post(strand.wrap(std::bind(&PrintNum, 1)));
    ioc->post(strand.wrap(std::bind(&PrintNum, 2)));

    std::this_thread::sleep_for(100ms);
    ioc->post(strand.wrap(std::bind(&PrintNum, 3)));
    ioc->post(strand.wrap(std::bind(&PrintNum, 4)));

    std::this_thread::sleep_for(100ms);
    ioc->post(strand.wrap(std::bind(&PrintNum, 5)));
    ioc->post(strand.wrap(std::bind(&PrintNum, 6)));
    work.reset();
}