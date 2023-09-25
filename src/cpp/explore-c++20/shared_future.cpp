#include <future>
#include <thread>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <random>

int query_number()
{
    std::cout << "enter a number: ";
    int num;
    std::cin >> num;

    if (!std::cin)
    {
        throw std::runtime_error("no number read");
    }
    return num;
}

void do_something(char c, std::shared_future<int> f, int sec = 400)
{
    try
    {
        int num = f.get();
        for (int i = 0; i < num; ++i)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(sec));
            std::cout.put(c).flush();
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "EXCEPTION in thread " << std::this_thread::get_id() << ": " << e.what() << std::endl;
    }
}

int main()
{
    auto d = std::bind(std::uniform_int_distribution(500, 2'000), std::mt19937(std::random_device{}()));
    try
    {
        std::shared_future<int> f = std::async(query_number);
        auto f1 = std::async(std::launch::async, do_something, '.', f, d());
        auto f2 = std::async(std::launch::async, do_something, '+', f, d());
        auto f3 = std::async(std::launch::async, do_something, '*', f, d());

        f1.get();
        f2.get();
        f3.get();
    }
    catch (const std::exception &e)
    {
        std::cerr << "\nEXCEPTION: " << e.what() << '\n';
    }
    std::cout << "\ndone" << std::endl;
}