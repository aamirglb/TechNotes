#include <iostream>
#include <thread>
#include <fmt/core.h>

void hello()
{
    std::cout << fmt::format("Hello C++ Concurrency") << std::endl;
}

int main()
{
    std::thread t(hello);
    std::cout << fmt::format("main thread started...") << std::endl;
    t.join();
}