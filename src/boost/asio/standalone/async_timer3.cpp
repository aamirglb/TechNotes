#include <iostream>
#include <functional>
#include <asio.hpp>

class printer {
public:
    printer(asio::io_context& io, int stop_count = 5)
    : timer_{io, asio::chrono::seconds{1}}
    , count_{0}
    , stop_coutn_{stop_count} {
        timer_.async_wait(std::bind(&printer::print, this));
    }

    ~printer() {
        std::cout << "Final count is " << count_ << std::endl;
    }

    void print() {
        if(count_ < stop_coutn_) {
            std::cout << "[printer]: " << count_ << std::endl;
            ++count_;

            timer_.expires_at(timer_.expiry() + asio::chrono::seconds(1));
            timer_.async_wait(std::bind(&printer::print, this));
        }
    }
private:
    asio::steady_timer timer_;
    int count_;
    int stop_coutn_;
};

int main() {
    asio::io_context io;
    printer p(io, 10);
    io.run();
}