#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <chrono>
#include <thread>

class fib_itr {
    size_t i {0};
    size_t f1 {0};
    size_t f2 {1};
public:
    fib_itr() = default;
    explicit fib_itr(size_t i_) : i{i_} {}
    size_t operator*() const { return f2; }
    fib_itr& operator++() {
        const size_t tmp {f2};
        f2 += f1;
        f1 = tmp;
        ++i;
        return *this;
    }

    bool operator!=(const fib_itr& other) const {
        return i != other.i;
    }
};

class fib_range {
    size_t end_n;
public:
    fib_range(size_t end) : end_n{end} {}
    fib_itr begin() const { return fib_itr{}; }
    fib_itr end()   const { return fib_itr{end_n}; }
};

int main() {
    std::cout << "size_t max value: " << std::numeric_limits<size_t>::max()
              << std::hex << " - " << std::numeric_limits<size_t>::max() << std::endl;
    std::cout << "#     | " << "fibonacci number\n";
    std::cout << "------|-----------------------\n";
    size_t cnt{};
    fib_range r {150};
    fib_itr itr = r.begin();
    size_t last_fib {};

    while(true) {
        std::cout << std::setw(5) << std::dec << ++cnt << " | "
                  << *itr << std::hex << " - " << *itr << "\n";

        last_fib = *itr;
        ++itr;
        if(last_fib > *itr) break;
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
// 0x1 11 f3 8a d0 84 0b f6 bf

    // for(int i = 0; i < 150; ++i) {
    //     std::cout << std::setw(5) << ++cnt << " | " << *itr << "\n";
    //     ++itr;
    // }
    // std::string line;
    // while(std::getchar (std::cin, line)) {
    //     std::cout << std::setw(5) << std::dec << ++cnt << " | "
    //               << *itr << std::hex << " - " << *itr << "\n";
    //     ++itr;
    // }
    // for(size_t i : fib_range(150)) {
    //     std::cout << std::setw(5) << ++cnt << " | " << i << "\n";
    // }

}