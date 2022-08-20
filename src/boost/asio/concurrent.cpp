// #include <iostream>

// void print1(void) {
//     for(int i = 0; i < 5; ++i) {
//         std::cout << "[print1] line: " << i << std::endl;
//     }
// }

// void print2(void) {
//     for(int i = 0; i < 5; ++i) {
//         std::cout << "[print2] line: " << i << std::endl;
//     }
// }

// int main() {
//     print1();
//     print2();
// }

#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <iostream>

void print1() {
    for(int i = 0; i < 5; ++i) {
        boost::this_thread::sleep_for(boost::chrono::milliseconds{500});
        std::cout << "[print1] line: " << i << std::endl;
    }
}

void print2() {
    for(int i = 0; i < 5; ++i) {
        boost::this_thread::sleep_for(boost::chrono::milliseconds{500});
        std::cout << "[print2] line: " << i << std::endl;
    }
}

int main() {
    boost::thread_group threads;
    threads.create_thread(print1);
    threads.create_thread(print2);
    threads.join_all();
}