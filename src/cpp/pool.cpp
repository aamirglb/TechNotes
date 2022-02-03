#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <random>


void do_work(uint32_t id) {
    static std::default_random_engine dre(id);
    std::uniform_int_distribution<int32_t> r(2000, 5000);
    auto wait_time = r(dre);
    std::cout << "Thread ID: " << id << " started, sleeping for " << wait_time << ".\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(wait_time));
    std::cout << "Thread ID: " << id << " finished.\n";
}

int main() {
    std::vector<std::thread> threads;
    for(auto i=0; i<20; ++i) {
        threads.emplace_back(do_work, i);
    }
    for(auto &t: threads)
        t.join();
}