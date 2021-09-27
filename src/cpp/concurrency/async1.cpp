// concurrency example of async

#include <future>
#include <thread>
#include <chrono>
#include <random>
#include <iostream>
#include <exception>

using namespace std;

struct Task {
    //Task(char c) : c_{c} {}
    char operator()() {

        std::default_random_engine dre(c_);
        std::uniform_int_distribution<int> id(10, 1000);

        for(auto i = 0; i < 10; ++i) {
            this_thread::sleep_for(chrono::milliseconds(id(dre)));
            cout.put(c_).flush();
        }
        return c_;
    }
int doSomething() {
    // random generator
    std::default_random_engine dre(c_);
    std::uniform_int_distribution<int> id(10, 1000);

    for(auto i = 0; i < 10; ++i) {
        this_thread::sleep_for(chrono::milliseconds(id(dre)));
        cout.put(c_).flush();
    }
    return c_;
}
    char c_='*';
};

int doSomething(char c) {
    // random generator
    std::default_random_engine dre(c);
    std::uniform_int_distribution<int> id(10, 1000);

    for(auto i = 0; i < 10; ++i) {
        this_thread::sleep_for(chrono::milliseconds(id(dre)));
        cout.put(c).flush();
    }
    return c;
}

int func1() {
    return doSomething('.');
}

int func2() {
    return doSomething('+');
}

int main() {
    std::cout << "starting func1() in background"
              << " and func2() in foreground:" << std::endl;

    std::future<int> result1(std::async(func1));

    //Task t('*');
    //std::future<int> result3(std::async(&Task::doSomething, &t));
    //std::future<int> result3(std::async(Task()));

    int result2 = func2();
    //int r3 = result3.get();
    int result = result1.get() + result2 + r3;
    std::cout << "\nResult of func1()+func2(): " << result << std::endl;
}