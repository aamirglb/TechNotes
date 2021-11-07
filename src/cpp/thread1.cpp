// Example of dettached thread
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <cstring>

using namespace std::chrono_literals;


    void func() {
        std::string filename = "/tmp/counter.txt";
        std::ofstream f;
        f.open(filename);
        uint32_t counter{};
        while(true) {
            std::this_thread::sleep_for(1s);
            auto now = std::chrono::system_clock::now();
            auto time = std::chrono::system_clock::to_time_t(now);
            auto stime = std::ctime(&time);
            stime[strlen(stime) - 1] = 0;

            f << "[" << stime << "] " << "counter value: " << counter++ << std::endl;
            f.flush();
            if(counter > 500) break;
        }
        f.close();
        std::cout << "thread finished\n";
    }
struct Counter {
    Counter() = default;

    void operator()() {
        std::string filename = "/tmp/counter.txt";
        std::ofstream f;
        f.open(filename);
        uint32_t counter{};
        while(true) {
            std::this_thread::sleep_for(1s);
            auto now = std::chrono::system_clock::now();
            auto time = std::chrono::system_clock::to_time_t(now);
            auto stime = std::ctime(&time);
            stime[strlen(stime) - 1] = 0;

            f << "[" << stime << "] " << "counter value: " << counter++ << std::endl;
            f.flush();
            if(counter > 500) break;
        }
        f.close();
        std::cout << "thread finished\n";
    }
};

int main() {
    //std::thread t(c);
    //std::thread t{Counter()};
    std::thread t(func);
    std::cout << "main thread started\n";
    t.detach();
    std::this_thread::sleep_for(15s);
    std::cout << "main thread finished\n";
}

