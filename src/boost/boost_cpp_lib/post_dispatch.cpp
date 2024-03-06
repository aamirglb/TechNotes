#include <asio.hpp>
#include <thread>
#include <iostream>

using namespace std::chrono_literals;

void fb()
{
    std::this_thread::sleep_for(1s);
    std::cout << std::this_thread::get_id() << " running B function\n";
}

bool start_a_function()
{
    std::cout << "Enter a non-empty string to run a function: ";
    std::string input;
    getline(std::cin, input);
    return input.length() == 0 ? false : true;
}

void fa(asio::io_context &ioc)
{
    static int selector = 0;
    std::cout << std::this_thread::get_id() << " starting a function." << std::endl;
    std::this_thread::sleep_for(3s);

    if (++selector % 2 == 0)
    {
        std::cout << std::this_thread::get_id() << " dispatching" << std::endl;
        ioc.dispatch(fb);
    }
    else
    {
        std::cout << std::this_thread::get_id() << " posting" << std::endl;
        ioc.post(fb);
    }
    std::cout << std::this_thread::get_id() << " exiting a function\n";
}

int main()
{
    std::cout << "Main Thread: " << std::this_thread::get_id() << std::endl;

    asio::io_context ioc;
    asio::io_context::work work(ioc);

    size_t count = 3;
    std::vector<std::jthread> threads;
    for (int i = 0; i < count; ++i)
    {
        // threads.emplace_back(std::bind(&asio::io_context::run, &ioc));
        threads.emplace_back([&]()
                             { ioc.run(); });
    }

    while (start_a_function())
    {
        ioc.post(std::bind(fa, std::ref(ioc)));
    }
    std::cout << "Stopping ASIO I/O Service..." << std::endl;
    ioc.stop();
    std::cout << "All threads terminated" << std::endl;
}
