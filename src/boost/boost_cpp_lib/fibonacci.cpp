#include <asio.hpp>
#include <chrono>
#include <thread>
#include <iostream>
#include <vector>
#include <random>
#include <mutex>

// The post function is used to ask the io_context to execute the given handler, but
// without allowing the io_service to call the handler from inside this function

// The dispatch function "guarantees that the handler will only be called in a thread in which the
// run(), run_one(), poll() or poll_one() member functions is currently being invoked. The handler may
// be executed insided this function if the guarantee can be met."

std::unordered_map<std::thread::id, int> thread_ids;
std::mutex stream_mutex;

using namespace std::chrono_literals;
using namespace std::placeholders;

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

size_t fib(size_t n)
{
    if (n <= 1)
    {
        return n;
    }
    std::this_thread::sleep_for(200ms);
    return fib(n - 1) + fib(n - 2);
}

void calculate_fib(size_t n)
{
    {
        std::scoped_lock<std::mutex> lock(stream_mutex);
        std::cout << "[" << std::this_thread::get_id() << "] Now calculating fib( " << n << " )" << std::endl;
    }

    size_t f = fib(n);

    {
        std::scoped_lock<std::mutex> lock(stream_mutex);
        std::cout << "[" << std::this_thread::get_id() << "] fib( " << n << " ) = " << f << std::endl;
    }
}

// The stop function will signal the io_context that all work should be stopped.

// The subtle difference is that dispatch() could even execute directly the passed function,
// where post() always request to io_service to run it.
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
    for (int i = 0; i < 2; ++i)
    {
        worker_threads.emplace_back(std::bind(WorkThread, ioc, i + 1));
    }

    for (int i = 3; i < 10; ++i)
    {
        ioc->post(std::bind(calculate_fib, i));
    }
    // ioc->dispatch(std::bind(calculate_fib, 7));
    // ioc->dispatch(std::bind(calculate_fib, 8));
    work.reset();
    ioc->run();
    // ioc->stop();
}