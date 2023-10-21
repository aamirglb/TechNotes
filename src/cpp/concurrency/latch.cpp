#include <thread>
#include <future>
#include <latch>
#include <barrier>
#include <random>
#include <ctime>
#include <iostream>
#include <vector>

class RandomGenerator
{
public:
    RandomGenerator(int min = 1, int max = 1000)
        : min_{min}, max_{max}, engine{rd()}, d{min_, max_}
    {
        // engine.seed(::time(nullptr));
    }

    int get_random_num()
    {
        return d(engine);
    }

private:
    int min_;
    int max_;
    std::random_device rd;
    std::mt19937 engine;
    std::uniform_int_distribution<int> d;
};

std::vector<int> latch_example()
{
    RandomGenerator rg;
    constexpr int thread_count{32};
    std::latch done{thread_count};

    int data[thread_count];
    std::vector<std::future<void>> futures;
    for (int i = 0; i < thread_count; ++i)
    {
        futures.push_back(std::async(std::launch::async, [&, i]
                                     {
            data[i] = rg.get_random_num();
            done.count_down();
            std::this_thread::sleep_for(std::chrono::milliseconds(data[i]));
            std::cout << "Thread-" << i+1 << " waiting for " << data[i] << " seconds."<< std::endl; }));
    }
    done.wait();
    return std::vector<int>(std::begin(data), std::end(data));
}

void barrier_example()
{
    constexpr int num_threads{16};

    std::barrier sync{num_threads};
    std::vector<std::jthread> threads(num_threads);

    std::vector<int> data;
    int result;

    // for(int i = 0; i < num_threads; ++i)
    // {
    //     threads[i] = std::jthread([&, i]{
    //         while()
    //     })
    // }
}

int main()
{
    // RandomGenerator rg;
    // for (int i = 0; i < 10; ++i)
    // {
    //     std::cout << i + 1 << " : " << rg.get_random_num() << std::endl;
    // }
    auto v = latch_example();
    for (int i{}; const auto &e : v)
    {
        std::cout << ++i << ": " << e << std::endl;
    }
}