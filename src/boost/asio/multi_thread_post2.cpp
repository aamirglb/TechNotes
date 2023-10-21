#include <asio.hpp>
#include <iostream>
#include <random>

using namespace std::chrono_literals;
using Duration = std::chrono::steady_clock::duration;

struct Task
{
    int id_;
    Duration delay_;

    void operator()() const
    {
        static int tid_gen{};
        thread_local const std::string tid = "[" + std::to_string(++tid_gen) + "] ";

        std::cout << tid << "Task-" << id_ << " started" << std::endl;
        std::this_thread::sleep_for(delay_);
        std::cout << tid << "Task-" << id_ << " finished after " << delay_ / 1.ms << "ms" << std::endl;
    }
};

int main()
{
    auto d = std::bind(std::uniform_int_distribution(500, 2'000), std::mt19937(std::random_device{}()));
    asio::thread_pool ctx(4);
    auto strand = asio::make_strand(ctx);

    for (int i = 1; i <= 8; ++i)
    {
        asio::post(asio::bind_executor(strand, Task{i, 1ms * d()}));
    }

    for (int i = 9; i <= 16; ++i)
    {
        asio::post(ctx, Task{i, 1ms * d()});
    }
    ctx.join();
}
