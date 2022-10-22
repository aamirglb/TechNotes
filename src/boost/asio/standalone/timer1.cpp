#include <iostream>
#include <asio.hpp>

int main(int argc, char *argv[]) {
    int32_t sec {5};
    if(argc > 1) {
        sec = std::stoi(argv[1]);
    }
    std::cout << "main started: waiting for " << sec << " seconds." << std::endl;
    asio::io_context io;
    asio::steady_timer t(io, asio::chrono::seconds(sec));
    t.wait();
    std::cout << "Hello, world!!" << std::endl;
}