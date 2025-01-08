#include <iostream>
#include <asio.hpp>

int main()
{
    asio::io_context io;
    auto work = asio::make_work_guard(io);
    // asio::executor_work_guard<decltype(io.get_executor())> work{io.get_executor()};
    io.run();
    std::cout << "This line will never get executed because io.run() blocks the execution" << std::endl;
}