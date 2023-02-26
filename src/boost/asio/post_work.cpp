#include <asio.hpp>
#include <iostream>
#include <thread>

int main()
{
    asio::io_context ctx;

    ctx.post([]
             { std::cout << "eat" << std::endl; });
    ctx.post([]
             { std::cout << "drink" << std::endl; });
    ctx.post([]
             { std::cout << "work" << std::endl; });

    std::jthread t([&]
                   { ctx.run(); });
    std::cout << "main thread - done." << std::endl;
}