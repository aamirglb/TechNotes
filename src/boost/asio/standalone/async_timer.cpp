#include <iostream>
#include <thread>
#include <asio.hpp>

void print(const asio::error_code& /* e */) {
    std::cout << "Hello, world!" << std::endl;
}

struct worker {
    worker(asio::io_context& io) : io_{io}
    {}

    void operator()() {
        io_.run();
    }

    asio::io_context& io_;
};

// void worker(asio::io_context &io) {
//     // while(true) {
//         io.run();
//     // }
// }

int main(int argc, char *argv[]) {
    int32_t sec {5};
    if(argc > 1) {
        sec = std::stoi(argv[1]);
    }

    std::cout << "main started: waiting for " << sec << " seconds." << std::endl;

    asio::io_context io;
    asio::steady_timer t(io, asio::chrono::seconds(sec));
    t.async_wait(&print);
    worker w(io);
    asio::thread th(w);

    int counter{};
    while(counter < 8) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "waiting for " << ++counter << std::endl;
    }
    th.join();
    // io.run();
}