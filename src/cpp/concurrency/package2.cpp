#include <utility>
#include <future>
#include <iostream>
#include <thread>
#include <deque>
#include <type_traits>
#include <vector>

class SumUp
{
public:
    int operator()(int beg, int end)
    {
        long long int sum{};
        for (int i = beg; i < end; ++i)
        {
            sum += i;
        }
        return sum;
    }
};

//     using TaskFunc = std::add_pointer<int(int, int)>::type;
int main()
{
    std::vector<SumUp> sums(4);
    std::vector<std::packaged_task<int(int, int)>> tasks;
    std::vector<std::future<int>> futures(4);

    tasks.reserve(4);
    for (int i = 0; i < 4; ++i)
    {
        tasks.push_back(std::packaged_task<int(int, int)>(sums[i]));
        futures[i] = tasks[i].get_future();
    }

    std::deque<std::packaged_task<int(int, int)>> all_tasks;
    for (int i = 0; i < 4; ++i)
    {
        all_tasks.push_back(std::move(tasks[i]));
    }

    int begin{1};
    int increment{2500};
    int end = begin + increment;

    while (!all_tasks.empty())
    {
        std::packaged_task<int(int, int)> curr_task = std::move(all_tasks.front());
        all_tasks.pop_front();

        std::thread sum_thread(std::move(curr_task), begin, end);
        begin = end;
        end += increment;
        sum_thread.detach();
    }

    // get results
    long long int sum{};
    for (int i = 0; i < 4; ++i)
    {
        sum += futures[i].get();
    }
    std::cout << "sum of 0 .. " << (25000 * 4) << " = " << sum << std::endl;
}