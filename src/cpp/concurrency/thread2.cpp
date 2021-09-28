#include <thread>
#include <chrono>
#include <random>
#include <iostream>
#include <exception>
#include <stdexcept>

using namespace std::chrono_literals;

void ThreadTask() {
    int32_t cnt = 5;

    while(cnt > 0) {
        std::this_thread::sleep_for(500ms);
        --cnt;
        if(cnt == 1) {
            throw std::runtime_error("no number read");
        }
    }
}

int main() {
    std::thread t(ThreadTask);
    std::this_thread::sleep_for(3s);
    t.join();
}