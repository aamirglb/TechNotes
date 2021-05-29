#include <thread>
#include <iostream>
#include <chrono>

struct func {
    int& i;
    func(int& i_): i{i_}{}
    void operator()() {
        std::cout<<std::this_thread::get_id() << '\n';
        using namespace std::chrono_literals;
        int sum{};
        for(auto i = 0; i < 10; ++i) {
            sum += i;
            std::this_thread::sleep_for(1s);
            std::cout << "summing up...\n";
        }
    }
};

void oops() {
    int some_local_state {};
    func f(some_local_state);
    std::thread t(f);
    t.detach();
    // t.join();
    std::cout << "oops exiting.\n";
}

int main() {
    std::cout<<std::this_thread::get_id() << '\n';
    oops();
    std::cout << "main returning.\n";
    return 0;
}