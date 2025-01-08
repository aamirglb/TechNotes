#include <iostream>
#include <asio.hpp>
#include <thread>

std::mutex g_stream_lock;

void print(std::string_view msg)
{
    std::scoped_lock<std::mutex> lock_guard(g_stream_lock);
    std::cout << "[" << std::this_thread::get_id() << "]: " << msg << std::endl;
}

void dispatch(int i)
{
    print( std::format("{} i = {}", __FUNCTION__, i));
}

void post(int i)
{
    print( std::format("{} i = {}", __FUNCTION__, i));
}

int main()
{
    // asio::thread_pool ctx(1);
    asio::io_context ioc;

    for(int i = 0; i < 10; ++i)
    {
        ioc.dispatch(std::bind(&dispatch, i*2+1));
        ioc.post(std::bind(&post, i*2));
        // asio::dispatch(ctx, std::bind(&dispatch, i*2+1));
        // asio::post(ctx, std::bind(&post, i*2));
    }
    ioc.run();
    // ctx.join();
}