#include <iostream>
#include <mutex>
#include <future>
#include <string>
#include <thread>

void task(std::timed_mutex& m, const std::string &name) {
    if(m.try_lock_for(std::chrono::seconds(1))) {
        std::lock_guard<std::timed_mutex> lg(m, std::adopt_lock);
        std::cout << name << " got the lock.\n";
    } else {
        std::cout << name << " could not get the lock.\n";
    }
}

int main() {
    std::timed_mutex m;
    std::thread t1(task, std::ref(m), "task-1");
    std::thread t2(task, std::ref(m), "task-2");

    t1.join();
    t2.join();
}