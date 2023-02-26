#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

std::atomic<bool> stop_flag{false};

void thread_func()
{
    while (!stop_flag.load(std::memory_order_relaxed))
    {
        std::cout << "Processing events..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(10));
        std::cout << "Events received..." << std::endl;
    }
}

int main()
{
    std::thread eventListener(thread_func);
    std::this_thread::sleep_for(std::chrono::seconds(3));
    stop_flag.store(true, std::memory_order_relaxed);
    eventListener.join();
    std::cout << "eventListener killed..." << std::endl;
}