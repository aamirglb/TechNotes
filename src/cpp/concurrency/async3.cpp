#include <iostream>
#include <future>
#include <chrono>

using namespace std;
using namespace std::chrono_literals;

std::future<int> f;
int quickComputation() {
    return 100;
}

int accurateComputation() {
    int count {20};
    while(count > 0) {
        --count;
        this_thread::sleep_for(1s);
        cout << "still computing accurate result...\n";
    }
    return 200;
}

int bestResultInTime() {
    // time-point
    auto tp = std::chrono::system_clock::now() + 10s;

    f = std::async(std::launch::async, accurateComputation);
    int guess = quickComputation();

    std::future_status s = f.wait_until(tp);

    if(s == std::future_status::ready) {
        return f.get();
    } else {
        cout << "timeout...\n";
        return guess;
    }
}

int main() {
    auto result = bestResultInTime();
    std::cout << "Best Result: " << result << std::endl;
}