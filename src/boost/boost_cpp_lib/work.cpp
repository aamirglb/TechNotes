#include <asio.hpp>
#include <iostream>

int main()
{
    asio::io_context ioc;
    asio::io_context::work work(ioc);
    ioc.run();
    std::cout << "Control should never come here!!" << std::endl;
}