#include <asio.hpp>
#include <iostream>
#include <thread>

using work_guard_type = asio::executor_work_guard<asio::io_context::executor_type>;

// destroy io_context::work to complete and return from io_context::run
void complete_work()
{
    asio::io_context ctx;
    auto work_guard = std::make_shared<work_guard_type>(ctx.get_executor());
    std::jthread watchdog([&, count = 0]() mutable
                          {
                              using namespace std::chrono_literals;
                              while (count < 10)
                              {
                                  ++count;
                                  std::cout << "%" << std::endl;
                                  std::this_thread::sleep_for(1s);
                              }
                              std::cout << "work done." << std::endl; });
}
int main()
{
    asio::io_context ctx;
    work_guard_type work_guard{ctx.get_executor()};
    using namespace std::chrono_literals;
    std::jthread watchdog([&, count = 0]() mutable
                          {
                             while (count < 11)
                             {
                                 ++count;
                                 std::cout << "%" << std::endl;
                                 std::cout.flush();
                                 std::this_thread::sleep_for(1s);
                             }
                             std::cout << std::endl;
                             ctx.stop(); });
    ctx.run();
    // std::cout << "Sorry, we'll never reach this!" << std::endl;
    std::cout << "We stopped after 10 seconds of running!!" << std::endl;
}