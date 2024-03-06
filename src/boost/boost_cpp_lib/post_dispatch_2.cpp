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

// Dispatched events can execute from the current worker thread even if
// there are other pending events queued up. The posted events have to wait
//  until the handler completes before being allowed to be executed.

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

void Dispatch(int x)
{
    std::scoped_lock<std::mutex> lock(stream_mutex);
    std::cout << "[" << std::this_thread::get_id() << "] "
              << __FUNCTION__ << " x = " << x << std::endl;
}

void Post(int x)
{
    std::scoped_lock<std::mutex> lock(stream_mutex);
    std::cout << "[" << std::this_thread::get_id() << "] "
              << __FUNCTION__ << " x = " << x << std::endl;
}

void run3(std::shared_ptr<asio::io_context> ioc)
{
    for (int x = 0; x < 3; ++x)
    {
        ioc->dispatch(std::bind(&Dispatch, x * 2));
        ioc->post(std::bind(&Post, x * 2 + 1));
        std::this_thread::sleep_for(1s);
    }
}

int main()
{
    std::cout << "main thread [" << std::this_thread::get_id() << "] started" << std::endl;
    auto ioc = std::make_shared<asio::io_context>();
    auto work = std::make_shared<asio::io_context::work>(*ioc);

    {
        std::scoped_lock<std::mutex> lock(stream_mutex);
        std::cout << "The program will exit when all work has finished." << std::endl;
    }

    std::vector<std::jthread> worker_threads;
    for (int i = 0; i < 1; ++i)
    {
        worker_threads.emplace_back(std::bind(WorkThread, ioc, i + 1));
    }
    ioc->post(std::bind(&run3, ioc));
    work.reset();
}