#include <asio.hpp>
#include <thread>
#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include <fmt/core.h>

using work_gurad_type = asio::executor_work_guard<asio::io_context::executor_type>;
using time_point = std::chrono::time_point<std::chrono::steady_clock>;
auto now = std::chrono::steady_clock::now;
using namespace std::chrono_literals;

class io_context_group
{
public:
    io_context_group(std::size_t size)
    {
        for (std::size_t n = 0; n < size; ++n)
        {
            contexts.emplace_back(std::make_shared<asio::io_context>());
            gurads.emplace_back(std::make_shared<work_gurad_type>(contexts.back()->get_executor()));
        }
    }

    void run()
    {
        for (auto &ctx : contexts)
        {
            threads.emplace_back([&]
                                 { ctx->run(); });
        }
    }

    asio::io_context &query()
    {
        return *contexts[index++ % contexts.size()];
    }

    ~io_context_group()
    {
        for (auto &thread : threads)
        {
            if (thread.joinable())
            {
                thread.join();
            }
        }
    }

private:
    template <typename T>
    using vector_ptr = std::vector<std::shared_ptr<T>>;

    vector_ptr<asio::io_context> contexts;
    vector_ptr<work_gurad_type> gurads;
    std::vector<std::thread> threads;
    std::atomic<std::size_t> index{};
};
std::mutex cout_mutex;

void timer_handler(size_t i, time_point start, asio::error_code ec)
{
    auto expired = fmt::format("timer-{} expired after: {}ms", i, (now() - start) / 1.0ms);

    if (ec == asio::error::operation_aborted)
    {
        std::cout << i + 1 << ": operation cancelled." << std::endl;
        return;
    }
    std::scoped_lock<std::mutex> lock(cout_mutex);
    std::cout << expired << std::endl;
}

int main()
{
    size_t count = std::thread::hardware_concurrency() * 2;
    io_context_group group(count);

    using Duration = std::chrono::steady_clock::duration;
    auto d = std::bind(std::uniform_int_distribution(10'000, 15'000), std::mt19937(std::random_device{}()));

    std::vector<std::shared_ptr<asio::steady_timer>> timers;
    for (size_t i = 0; i < count; ++i)
    {
        auto delay = d();
        auto ptr = std::make_shared<asio::steady_timer>(group.query(), std::chrono::steady_clock::now() + (1s * i));
        timers.emplace_back(std::move(ptr));
        timers.back()->async_wait([&, i = i, n = now()](asio::error_code ec)
                                  { timer_handler(i + 1, n, ec); });

        std::cout << i + 1 << ": " << delay << std::endl;
    }

    group.run();
    char ch;
    std::cin >> ch;
}