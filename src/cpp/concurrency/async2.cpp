#include <future>
#include <list>
#include <iostream>
#include <exception>
#include <chrono>

using namespace std;

struct MyException : public exception {
    const char* what() const throw() {
        return "Attempt to divide by zero\n";
    }
};

void task1() {
    int32_t d = 5;
    int32_t counter = 10;
    while(counter > 0) {
        --counter;
        --d;
        if(d==0) {
            MyException e;
            throw e;
        }
        int32_t result = counter / d;
        std::this_thread::sleep_for(chrono::milliseconds(300));
    }
}

int main() {
    cout << "starting 2 task" << endl;
    std::future<void> f1 = async(task1);
    cin.get();
    cout << "\n wait for end of task1: " << endl;
    try {
        f1.get();
    } catch(const exception& e) {
        cerr << "EXCEPTION: " << e.what() << endl;
    }
}