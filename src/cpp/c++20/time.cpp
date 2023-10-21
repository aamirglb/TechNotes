#include <ctime>
#include <chrono>
#include <iostream>
#include <thread>
#include <iomanip>

void diff_clocks()
{
    std::chrono::system_clock::time_point pc_clock = std::chrono::system_clock::now();
    std::time_t pc_clock_time = std::chrono::system_clock::to_time_t(pc_clock);
    std::cout << "The time according to computer clock is: " << 
        std::put_time(std::localtime(&pc_clock_time), "%T %p") << std::endl;

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    std::chrono::high_resolution_clock::time_point start2 = std::chrono::high_resolution_clock::now();
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    // current time
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::cout << "\n\nThe time now is: " << std::put_time(std::localtime(&now_c),
        "%F %T %b %I %p") << std::endl;
    std::time_t now_p = std::chrono::system_clock::to_time_t(now - std::chrono::hours(2));
    std::cout << "The time 2 hours ago was: " << std::put_time(std::localtime(&now_p),
        "%F %T %B %A") << "\n" << std::endl;

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::chrono::high_resolution_clock::time_point end2 = std::chrono::high_resolution_clock::now();
    std::cout << "Computing lasted " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << 
        " microseconds!" << std::endl;

    std::cout << "Computing with hight_resolution_clock yielded " << 
        std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - start2).count() << " nanoseconds!" << std::endl;
}

int main()
{
    auto timepoint = std::chrono::system_clock::now();
    auto currentTime = std::chrono::system_clock::to_time_t( timepoint );
    auto timeText = std::ctime(&currentTime);

    std::cout << timeText << std::endl;

    using namespace std::chrono_literals;
    auto start = std::chrono::system_clock::now();
    std::this_thread::sleep_for(5s);
    auto end = std::chrono::system_clock::now();

    auto timeTaken = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Time Taken: " << timeTaken.count() << std::endl;
    std::cout << std::endl;

    diff_clocks();
}