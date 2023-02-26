#include <iostream>
#include <thread>
#include <algorithm>
#include <numeric>
#include <vector>

template <typename Iterator, typename T>
struct accumulate_block
{
    void operator()(Iterator first, Iterator last, T &result, std::thread::id &id_ref)
    {
        std::cout << "Thread id = " << std::this_thread::get_id() << std::endl;
        id_ref = std::this_thread::get_id();
        result = std::accumulate(first, last, result);
    }
};

template <typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init)
{
    const unsigned long length = std::distance(first, last);
    if (!length)
    {
        return init;
    }
    const unsigned long min_per_thread{25};
    const unsigned long max_threads = (length + min_per_thread - 1) / min_per_thread;
    const unsigned long hardware_threads = std::thread::hardware_concurrency();
    std::cout << "hardware threads = " << hardware_threads << std::endl;
    const unsigned long num_threads = std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);
    const unsigned long block_size = length / num_threads;

    std::vector<T> results(num_threads);
    std::vector<std::thread> threads(num_threads - 1);
    std::vector<std::thread::id> thread_ids(num_threads);

    Iterator block_start = first;

    for (unsigned long i = 0; i < (num_threads - 1); ++i)
    {
        Iterator block_end = block_start;
        std::advance(block_end, block_size);
        threads[i] = std::thread(
            accumulate_block<Iterator, T>(),
            block_start,
            block_end,
            std::ref(results[i]),
            std::ref(thread_ids[i]));
        block_start = block_end;
    }
    accumulate_block<Iterator, T>()(block_start, last, results[num_threads - 1], thread_ids[num_threads - 1]);

    for (auto &entry : threads)
        entry.join();

    unsigned long int sum{};
    for (int i = 0; const auto &e : results)
    {
        sum += results[i];
        std::cout << thread_ids[i] << " - results[" << i << "] = " << results[i] << " = " << sum << std::endl;

        ++i;
    }
    return std::accumulate(results.begin(), results.end(), init);
}

int main()
{
    std::vector<unsigned int> nums(100'000);
    std::cout << std::numeric_limits<unsigned int>::max() << " --  " << std::numeric_limits<unsigned int>::max() / 2000 << std::endl;
    std::iota(nums.begin(), nums.end(), 0);

    auto result = parallel_accumulate(nums.begin(), nums.end(), 0UL);
    std::cout << "Final Result = " << result << std::endl;
}