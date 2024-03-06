#include <asio.hpp>
#include <iostream>
#include <memory>

int main()
{
    asio::io_context ioc;
    auto work = std::make_shared<asio::io_context::work>(ioc);
    work.reset();

    ioc.run();
    std::cout << "Control SHOULD come here!!" << std::endl;
}