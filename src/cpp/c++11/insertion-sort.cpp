// insertion sort algorithm

#include <iostream>
#include <vector>
#include <string>
#include <random>

void insertionSort(std::vector<int32_t> &v) {
    int32_t n = v.size();

    for(int32_t pass = 1; pass < n; ++pass) {
        auto x = v[pass];
        auto j = pass - 1;

        // shift elements to the right
        while(j >= 0 && v[j] > x) {
            v[j+1] = v[j];
            --j;
        }
        v[j+1] = x;
    }
}

int main(int32_t argc, char* argv[]) {
    int32_t n {10};

    if(argc >= 2) {
        n = std::stoi(argv[1]);
    }

    std::random_device d;
    std::default_random_engine e(d());
    std::uniform_int_distribution<int32_t> ds(-10, 50);

    std::vector<int32_t> v(n, 0);
    for(int32_t i = 0; i < n; ++i) {
        v[i] = ds(e);
    }

    std::cout << "Before sort n = " << n << std::endl;
    for(const auto& e: v) std::cout << e << ' ';
    std::cout << std::endl;

    insertionSort(v);
    std::cout << "After Insertion sort n = " << n << std::endl;
    for(const auto& e: v) std::cout << e << ' ';
    std::cout << std::endl;
}