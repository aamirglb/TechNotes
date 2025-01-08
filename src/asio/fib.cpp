#include <iostream>
#include <thread>
#include <chrono>
#include <functional>
#include <mutex>
#include <asio.hpp>
#include <unordered_map>

using namespace std::chrono_literals;

std::mutex g_stream_lock;
std::unordered_map<std::thread::id, std::string> thread_names;

void print(std::string_view msg)
{
    std::scoped_lock<std::mutex> lock_guard(g_stream_lock);
    std::cout << "[" << std::this_thread::get_id() << "]: " << msg << std::endl;
    // std::cout << "[" << thread_names[std::this_thread::get_id()] << "]: " << msg << std::endl;
}

void WorkerThread(std::shared_ptr<asio::io_context> ioc, int id)
{
    thread_names[std::this_thread::get_id()] = std::format("t{}", id);
    print("Thread Started ");
    ioc->run();
    print("Thread Finished ");
}

size_t fib(size_t n)
{
    if(n <= 1)
    {
        return n;
    }

    std::this_thread::sleep_for(100ms);
    return fib(n-1) + fib(n-2);
}

void CalculateFib(size_t n)
{
    print(std::format("Now calculating fib({})", n));
    size_t f = fib(n);
    print(std::format("fib({}) = {}", n, f));
}

// Use asio::thread_pool
int main()
{
    thread_names[std::this_thread::get_id()] = "main";
    // std::shared_ptr<asio::io_context> ioc = std::make_shared<asio::io_context>();
    // auto worker = asio::make_work_guard(*ioc);
    asio::thread_pool ctx(4);
    auto worker = asio::make_work_guard(ctx);

    print("The program will exit when all work has finished.");

    std::jthread stop_thread([&ctx, &worker]() {
        std::cin.get();
        worker.reset();
        ctx.join();
    });

    for(int i = 4; i < 11; ++i)
    {
        print(std::format("posting fib(i)"));
        asio::post(std::bind(CalculateFib, i));
    }
    return 0;
}

// Use std::thread
// int main()
// {
//     thread_names[std::this_thread::get_id()] = "main";
//     std::shared_ptr<asio::io_context> ioc = std::make_shared<asio::io_context>();
//     auto worker = asio::make_work_guard(*ioc);

//     print("The program will exit when all work has finished.");
//     std::vector<std::jthread> worker_threads;

//     for(int i = 0; i < 3; ++i)
//     {
//         worker_threads.emplace_back(std::bind(&WorkerThread, ioc, i+1));
//     }

//     std::jthread stop_thread([ioc, &worker]() {
//         std::cin.get();
//         worker.reset();
//         ioc->stop();
//     });

//     for(int i = 4; i < 11; ++i)
//     {
//         print(std::format("posting fib(i)"));
//         ioc->post(std::bind(CalculateFib, i));
//     }
//     ioc->run();
//     // ioc->post(std::bind(CalculateFib, 6));
//     // ioc->post(std::bind(CalculateFib, 5));
//     // ioc->post(std::bind(CalculateFib, 4));

//     // worker.reset();
//     return 0;
// }


