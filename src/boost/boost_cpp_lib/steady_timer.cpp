#include <asio.hpp>
#include <asio/steady_timer.hpp>
#include <chrono>
#include <iostream>

using namespace asio;
io_context ioc;

void on_timeout(const error_code &ec);
std::int32_t max_sec{1};
std::vector<std::shared_ptr<steady_timer>> timers;
void create_new_timer()
{
    timers.emplace_back(std::make_shared<steady_timer>(ioc, std::chrono::seconds(max_sec++)));
    // auto timer = new steady_timer(ioc, std::chrono::seconds(3));
    // steady_timer timer{ioc, std::chrono::seconds{3}};
    timers.back()->async_wait(on_timeout);
}

void on_timeout(const error_code &ec)
{
    if (ec == asio::error::timed_out)
    {
        std::cout << "timer timeout\n";
    }
    if (ec == asio::error::operation_aborted)
    {
        std::cout << "operation aborted\n";
    }

    if (!ec)
    {
        std::cout << "timer expired without any error\n";
        create_new_timer();
    }
}

int main()
{
    create_new_timer();
    // timer.async_wait([&t = timer](const error_code &ec)
    //                  {
    //                 std::cout << "handler thread id: " << std::this_thread::get_id() << std::endl;
    //                 std::cout << "3 seconds elapsed\n"; });
    // error_code ec;
    // timer.wait(ec);
    std::cout << "main thread id: " << std::this_thread::get_id() << std::endl;
    // std::cout << "main thread starting work\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    // std::cout << "main thread wokeup after 1 second\n";

    ioc.run();
}