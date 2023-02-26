#include <iostream>
#include <thread>
#include <chrono>
#include <fmt/core.h>
#include <fmt/color.h>

void create_threads()
{
    int local_state{};
    std::thread t1{
        [&local_state]()
        {
            while (local_state < 10)
            {
                std::cout << fmt::format(fmt::fg(fmt::rgb(0xFFFF00)), "lambda: {}", local_state) << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
        }};
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    // t1.detach();
}

int main()
{
    std::thread t2{create_threads};
    t2.join();
    std::cout << "main thread exiting..." << std::endl;
}