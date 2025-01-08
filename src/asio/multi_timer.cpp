#include <iostream>
#include <thread>
#include <chrono>
#include <asio.hpp>
#include <string>
#include <memory>
#include <unordered_map>

using namespace std::chrono_literals;
std::unordered_map<std::thread::id, std::string> thread_names;

using StrandSharedPtr = std::shared_ptr<asio::strand<asio::io_context::executor_type>>;

class printer
{
public:
  printer(std::shared_ptr<asio::io_context> ioc, StrandSharedPtr strand, int id, int stop_count)
    : timer_(*ioc, 500ms),
      strand_(strand),
      id_(id),
      count_(0),
      stop_count_(stop_count)
  {
    timer_.async_wait(std::bind(&printer::print, this));
  }

  ~printer()
  {
    std::cout << "Final count is " << count_ << std::endl;
  }

  void print()
  {
    if (count_ < stop_count_)
    {
        auto name = thread_names[std::this_thread::get_id()];
      std::cout << std::format("{}\t[printer-{}]: {}", name, id_, count_) << std::endl;
    //   std::cout << count_ << std::endl;
      ++count_;
      timer_.expires_at(timer_.expiry() + 500ms);
    //   timer_.async_wait(std::bind(&printer::print, this));
      timer_.async_wait(asio::bind_executor(*strand_, std::bind(&printer::print, this)));
    }
  }

private: 
  asio::steady_timer timer_;
  StrandSharedPtr strand_;
  int id_;
  int count_;
  int stop_count_;
};

int main()
{
    thread_names[std::this_thread::get_id()] = "main";
    std::shared_ptr<asio::io_context> ioc = std::make_shared<asio::io_context>();
    auto strand = std::make_shared<asio::strand<asio::io_context::executor_type>>(asio::make_strand(*ioc));
    auto work = asio::make_work_guard(*ioc);

    std::vector<std::unique_ptr<printer>> printers;
    for(int i = 0; i < 10; ++i)
    {
        printers.push_back(std::make_unique<printer>(ioc, strand, i+1, (i+1)*3));
    }
    std::jthread thrd( [ioc](){
        thread_names[std::this_thread::get_id()] = "t1";
        ioc->run(); 
    });
    // all handlers will be called by main thread
    ioc->run();
    return 0;
}

