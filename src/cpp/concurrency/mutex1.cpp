#include <future>
#include <mutex>
#include <iostream>
#include <string>

std::mutex printMutex;

void print(const std::string& s) {
    using namespace std::chrono_literals;
    //std::lock_guard<std::mutex> mlock(printMutex);
    for(char c : s) {
        std::cout.put(c).flush();
        std::this_thread::sleep_for(100ms);
    }
    std::cout << std::endl;
}

int main() {
    auto f1 = std::async(std::launch::async,
        print, "Hello from a first thread");
    auto f2 = std::async(std::launch::async,
        print, "Hello from a second thread");
    print("Hello from the main thread");
}