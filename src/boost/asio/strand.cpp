#include <asio.hpp>
#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <unordered_set>

#include <fmt/format.h>
#include <fmt/chrono.h>

void timer_expired(std::string id)
{
    using namespace std::chrono_literals;
    std::cout << fmt::format("{:%d-%m-%Y %H:%M:%S} - {} entered.", std::chrono::system_clock::now(), id) << std::endl;
    std::this_thread::sleep_for(3s);
    std::cout << fmt::format("{:%d-%m-%Y %H:%M:%S} - {} leave.", std::chrono::system_clock::now(), id) << std::endl;
}

int main()
{
    asio::io_context ctx;
    asio::io_context::strand strand(ctx);

    using namespace std::chrono_literals;
    asio::steady_timer timer1(ctx, 5s);
    asio::steady_timer timer2(ctx, 5s);
    asio::steady_timer timer3(ctx, 6s);

    timer1.async_wait(strand.wrap([](auto... vn)
                                  { timer_expired("timer-1"); }));

    timer2.async_wait(strand.wrap([](auto... vn)
                                  { timer_expired("timer-2"); }));

    timer3.async_wait([](auto... vn)
                      { timer_expired("timer-3"); });

    std::jthread t1([&]
                    { ctx.run(); });
    std::jthread t2([&]
                    { ctx.run(); });

    std::cout << "main thread - done. " << std::endl;

    std::cout << std::endl
              << std::endl;

#include <iostream>
#include <unordered_set>
#include <typeinfo>

#define PRINT_NAME(x) std::cout << #x << " - " << typeid(x).name() << '\n'

    {
        PRINT_NAME(char);
        PRINT_NAME(signed char);
        PRINT_NAME(unsigned char);
        PRINT_NAME(short);
        PRINT_NAME(unsigned short);
        PRINT_NAME(int);
        PRINT_NAME(unsigned int);
        PRINT_NAME(long);
        PRINT_NAME(unsigned long);
        PRINT_NAME(float);
        PRINT_NAME(double);
        PRINT_NAME(long double);
        PRINT_NAME(char *);
        PRINT_NAME(const char *);

        static std::unordered_set<int> s{2, 4, 6, 8, 10, 12};
        int key{2};
        auto count{s.count(key)};
        std::cout << typeid(count).name() << std::endl;
    }
}