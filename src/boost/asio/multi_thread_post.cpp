#include <asio.hpp>
#include <thread>
#include <iostream>
#include <vector>
#include <random>

struct Task
{
    Task(int id, int wait_time)
        : id_{id}, wait_time_{wait_time}
    {
    }

    void operator()()
    {
        std::cout << "Tast-" << id_ << " started. [" << std::this_thread::get_id() << "]" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(wait_time_));
        std::cout << "Task-" << id_ << " finished after (" << wait_time_
                  << ") milliseconds. [" << std::this_thread::get_id() << "]" << std::endl;
    }
    int id_;
    int wait_time_;
};

int main()
{
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution d(500, 2'000);

    asio::io_context ctx;
    asio::io_context::strand strand(ctx);

    std::vector<std::jthread> threads;
    auto count = 4; // std::thread::hardware_concurrency() * 2;

    for (int i = 0; i < count * 2; ++i)
    {
        // asio::post(Task(i + 1, d(engine)));
        asio::post(strand.wrap(Task(i + 1, d(engine))));
    }

    for (int i = 0; i < count; ++i)
    {
        threads.emplace_back([&]
                             { ctx.run(); });
    }
    ctx.run();
}

/*
.\build-msvc\Debug\multi_thread_post.exe
Tast-Tast-32 started. [76636]Tast-22 started. [14368]Tast-4 started. [1 started. [68184]
Tast-18 started. [Tast-15 started. [Tast-13 started. [Tast-27 started. [Tast-11 started. [Tast-9 started. [Tast-10 started. [Tast-25 started. [Tast-29 started. [62584]Tast-21 started. [83096]

Tast-31 started. [35040]Tast-17 started. [Tast-16 started. [Tast-14 started. [Tast-Tast-23Tast-26 started. [19376]Tast-19 started. [51064]Tast-3 started. [
75468]

Tast-2 started. [Tast-30 started. [68616]Tast-6 started. [60388]12 started. [46268]56672]
Tast-8 started. [6748]21920]26888]68524]25256]

Tast-7 started. [268]
Tast-5 started. [70104]84132]24464]

37884]

71656]


Tast-28 started. [46844]

18112]
Tast-24 started. [47804]
48952]
 started. [59916]

Tast-20 started. [49260]
30060]

68940]




Task-32 finished after (1270) milliseconds. [76636]
Task-23 finished after (2157) milliseconds. [59916]
Task-6 finished after (2728) milliseconds. [48952]
Task-17 finished after (2869) milliseconds. [25256]
Task-22 finished after (3033) milliseconds. [14368]
Task-13 finished after (3837) milliseconds. [68616]
Task-30 finished after (3963) milliseconds. [24464]
Task-19 finished after (4089) milliseconds. [18112]
Task-28 finished after (4107) milliseconds. [46844]
Task-10 finished after (4215) milliseconds. [84132]
Task-16 finished after (4282) milliseconds. [21920]
Task-2 finished after (4378) milliseconds. [70104]
Task-26 finished after (4411) milliseconds. [19376]
Task-29 finished after (4537) milliseconds. [62584]
Task-3 finished after (4694) milliseconds. [75468]
Task-15 finished after (5186) milliseconds. [56672]
Task-12 finished after (5253) milliseconds. [71656]
Task-4 finished after (5406) milliseconds. [51064]
Task-25 finished after (5784) milliseconds. [26888]
Task-27 finished after (5803) milliseconds. [60388]
Task-7 finished after (6052) milliseconds. [268]
Task-18 finished after (6072) milliseconds. [68524]
Task-14 finished after (6346) milliseconds. [46268]
Task-8 finished after (6374) milliseconds. [6748]
Task-31 finished after (6630) milliseconds. [35040]
Task-21 finished after (7304) milliseconds. [83096]
Task-9 finished after (7641) milliseconds. [30060]
Task-1 finished after (8041) milliseconds. [68184]
Task-24 finished after (8229) milliseconds. [47804]
Task-5 finished after (8900) milliseconds. [68940]
Task-20 finished after (9260) milliseconds. [49260]
Task-11 finished after (9697) milliseconds. [37884]

*/