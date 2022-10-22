#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

#include <asio.hpp>

class printer {
public:
    printer(asio::io_context& io, int stop_count = 10)
        : strand_{asio::make_strand(io)}
        , timer1_{io, asio::chrono::seconds(1)}
        , timer2_{io, asio::chrono::seconds(1)}
        , count_{0}
        , stop_count_{stop_count}
    {
        timer1_.async_wait(asio::bind_executor(strand_,
            std::bind(&printer::print1, this)));

        timer2_.async_wait(asio::bind_executor(strand_,
            std::bind(&printer::print2, this)));
    }

    ~printer() {
        std::cout << "Final count is: " << count_ << std::endl;
    }

    void print1() {
        if(count_ < stop_count_) {
            std::cout << "Timer 1: " << count_ << std::endl;
            ++count_;

            timer1_.expires_at(timer1_.expiry() + asio::chrono::seconds(1));
            timer1_.async_wait(asio::bind_executor(strand_,
                std::bind(&printer::print1, this)));
        }
    }

    void print2() {
    if(count_ < stop_count_) {
        std::cout << "Timer 2: " << count_ << std::endl;
        ++count_;

        timer2_.expires_at(timer2_.expiry() + asio::chrono::seconds(1));
        timer2_.async_wait(asio::bind_executor(strand_,
            std::bind(&printer::print2, this)));
        }
    }

private:
    asio::strand<asio::io_context::executor_type> strand_;
    asio::steady_timer timer1_;
    asio::steady_timer timer2_;
    int count_;
    int stop_count_;
};

int main() {
    // asio::io_context io;
    // printer p(io, 15);
    // // asio::thread t(std::bind(&asio::io_context::run, &io));
    // asio::thread t([&io](){io.run();});
    // io.run();
    // t.join();

    std::vector<int> nums= {3,2,1,0,2,3,3,1,0,0};
    auto m = std::max_element(nums.rbegin(), nums.rend());
    std::cout << "distance: " << std::distance(nums.rend(), m) << std::endl;
    std::cout << *m << std::endl;
}