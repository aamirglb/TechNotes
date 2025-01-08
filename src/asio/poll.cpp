#include <iostream>
#include <chrono>
#include <thread>

#include <asio.hpp>

using namespace std::chrono_literals;

class printer {
public:
    printer(asio::io_context& io, int stop_count = 30)
    : timer_{io, 200ms}
    , count_{0}
    , stop_count_{stop_count} {
        timer_.async_wait(std::bind(&printer::print, this));
    }

    ~printer() {
        std::cout << "Final count is " << count_ << std::endl;
    }

    void print() {
        if(count_ < stop_count_) {
            std::cout << "[printer]: " << count_ << std::endl;
            ++count_;

            timer_.expires_at(timer_.expiry() + 200ms);
            timer_.async_wait(std::bind(&printer::print, this));
        }
    }
private:
    asio::steady_timer timer_;
    int count_;
    int stop_count_;
};

int main()
{
    asio::io_context ioc;
    // asio::io_context::work work{ioc};
    printer p(ioc, 20);

    for(int i = 0; i < 10; ++i)
    {
        ioc.poll();
        std::this_thread::sleep_for(200ms);
        std::cout << "counter = " << i << std::endl;
    }
    ioc.run();
}