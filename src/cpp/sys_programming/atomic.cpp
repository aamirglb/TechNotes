// g++ -Wall atomic.cpp -latomic
#include <iostream>
#include <utility>
#include <atomic>

struct MyArray { int z[50]; };
struct MyStr { int a; int b; };

int main()
{
    std::atomic<MyArray> myArray;
    std::atomic<MyStr> myStr;
    std::cout << std::boolalpha
        << "myArray is lock free? "
        << std::atomic_is_lock_free(&myArray) << '\n'
        << "myStr is lock free? "
        << std::atomic_is_lock_free(&myStr) << std::endl;
}
