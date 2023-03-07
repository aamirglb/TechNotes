#include <asio.hpp>
#include <iostream>
#include <thread>

using namespace std::chrono_literals;
auto now = std::chrono::high_resolution_clock::now;
asio::io_context ctx;
asio::high_resolution_timer timer(ctx);
auto begin = now();

void async_wait()
{
    timer.expires_after(1s);
    timer.async_wait([&](asio::error_code ec)
                     {
        if(ec == asio::error::operation_aborted)
        {
            std::cout << "The timer is cancelled\n";
            return;
        }
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now() - begin).count();
        std::cout << elapsed << "s" << std::endl;
        async_wait(); });
}

int main(int argc, char *argv[])
{
    int duration{10};
    if (argc > 1)
    {
        duration = std::stoi(argv[1]);
    }
    async_wait();
    std::thread t([]
                  { ctx.run(); });
    std::this_thread::sleep_for(1s * duration);
    timer.cancel();
    t.join();
}