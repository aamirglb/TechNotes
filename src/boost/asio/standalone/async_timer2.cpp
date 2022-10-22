#include <iostream>
#include <thread>
#include <functional>

#include <asio.hpp>

void print(const asio::error_code& /*e*/,
           asio::steady_timer* t,
           int* counter) {
    if(*counter < 10) {
        std::cout << *counter << std::endl;
        ++(*counter);
        t->expires_at(t->expiry() + asio::chrono::seconds(1));
        t->async_wait(std::bind(print, std::placeholders::_1, t, counter));
    }
}

void worker(asio::io_context *io) {
    io->run();
}

int main() {
    asio::io_context io;
    int count {};

    asio::steady_timer t(io, asio::chrono::seconds(1));
    t.async_wait(std::bind(print, std::placeholders::_1, &t, &count));

    asio::thread th(std::bind(worker, &io));
    // io.run();
    int c{};
    while(c < 15) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "main thread doing work...\n";
        ++c;
    }
    std::cout << "Final count is " << count << std::endl;
    th.join();
}
