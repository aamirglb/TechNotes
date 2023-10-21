#include <thread>
#include <chrono>
#include <iostream>
#include <fmt/core.h>
#include <fmt/color.h>

class background_task
{
public:
    void operator()(int counter = 10, int color = 0xFF0000) const
    {
        while (counter >= 0)
        {
            std::cout << fmt::format(fg(fmt::rgb(color)), "background_task: {}\n", counter) << std::endl;
            --counter;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }
};

int main()
{
    int global{1};
    background_task task1;
    background_task task2;

    // C++'s most vexing parse, try to pass a temporary object
    // std::thread t1(background_task());
    std::thread t1(task1);
    std::thread t2(task2, 10, 0x00FFFF);

    // clang-format off
    std::thread t3{[&global, counter = 15]() mutable
    {
        while (counter >= 0)
        {
            std::cout << fmt::format(fg(fmt::rgb(0xFFFF00)), "lambda: {}, global = {}\n", counter, global) << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1100));
            --counter;
        }
    }};
    // clang-format on

    int counter = 15;
    while (counter >= 0)
    {
        std::cout << fmt::format(fg(fmt::rgb(0x00FF00)), "main_thred: {}\n", counter) << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(950));
        if (counter == 7)
        {
            global = 50;
        }
        --counter;
    }
    t1.join();
    t2.join();
    t3.join();
}