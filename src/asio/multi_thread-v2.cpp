#include <iostream>
#include <thread>
#include <chrono>
#include <asio.hpp>
#include <string>
#include <memory>
#include <unordered_map>

using namespace std::chrono_literals;
std::unordered_map<std::thread::id, std::string> thread_ids;
std::unordered_map<std::thread::id, int32_t> work_count;

void WorkerThread(std::shared_ptr<asio::io_context> ioc, int id)
{
    thread_ids[std::this_thread::get_id()] = std::format("THREAD-{}", id);
    std::cout << "Thread Started: " << std::this_thread::get_id() << std::endl;
    ioc->run();
    std::cout << "Thread Finished\n";
}

class printer {
public:
    printer(std::shared_ptr<asio::io_context> io, int stop_count = 30)
    : timer_{*io, 200ms}
    , count_{0}
    , stop_count_{stop_count} {
        timer_.async_wait(std::bind(&printer::print, this));
    }

    ~printer() {
        std::cout << "Final count is " << count_ << std::endl;
    }

    void print() {
        if(count_ < stop_count_) {
            work_count[std::this_thread::get_id()] += 1; 
            std::cout << std::format("[printer - {}]: {}\n", thread_ids[std::this_thread::get_id()], count_);
            // std::cout << "[printer]: " << count_ <<  std::endl;
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
    std::shared_ptr<asio::io_context> ioc = std::make_shared<asio::io_context>();
    auto work = asio::make_work_guard(*ioc);

    std::cout << "Press [return] to exit." << std::endl;
    std::vector<std::jthread> worker_threads;
    for(int i = 0; i < 4; ++i)
    {
        std::jthread t(WorkerThread, ioc, i+1);
        worker_threads.push_back(std::move(t));
    }

    std::vector<std::unique_ptr<printer>> printers;
    for(int i = 0; i < 10; ++i)
    {
        printers.push_back(std::make_unique<printer>(ioc));
    }
    // printer p1(ioc);
    // printer p2(ioc);

    std::cin.get();
    ioc->stop();
    std::cout << "Handler execution summary: " << std::endl;
    for(const auto& [id, count] : work_count)
    {
        std::cout << std::format("{} = {}\n", thread_ids[id], work_count[id]);
    }
    return 0;
}

