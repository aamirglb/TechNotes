#include <iostream>
#include <thread>
#include <chrono>
#include <stdexcept>
#include <cstdlib>

class thread_guard
{
    std::thread &t;

public:
    explicit thread_guard(std::thread &t_) : t{t_}
    {
    }
    ~thread_guard()
    {
        if (t.joinable())
        {
            std::cout << "Joining thread in destructor." << std::endl;
            t.join();
        }
    }
    // non-copyable
    thread_guard(const thread_guard &) = delete;
    // non-assignable
    thread_guard &operator=(const thread_guard &) = delete;
};

struct func
{
    int &i;
    func(int &i_) : i{i_}
    {
    }

    void operator()()
    {
        while (i > 0)
        {
            std::cout << "func running: " << i << std::endl;
            --i;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }
};

void f()
{
    int data{12};
    int sleep_time{13'000};

    func my_func{data};
    std::thread t(my_func);
    thread_guard guard{t};
    std::srand(static_cast<unsigned int>(time(nullptr)));
    bool throw_exception{false};

    if (rand() % 2 == 0)
    {
        sleep_time = 4'500;
        throw_exception = true;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
    if (throw_exception)
    {
        throw std::out_of_range{"out of range"};
    }
}

int main()
{
    try
    {
        f();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}