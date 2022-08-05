// Selection sort algorithm

#include <iostream>
#include <vector>
#include <string>
#include <random>

// sort elements with minimum swaps
void selectionSort(std::vector<int32_t> &v) {
    int32_t n = v.size();

    for(int32_t i = 0; i < n - 1; ++i) {
        int32_t j = i;
        int32_t k = i;
        for(; j<n; ++j) {
            if(v[j] < v[k]) {
                k = j;
            }
        }
        std::swap(v[k], v[i]);
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

    selectionSort(v);
    std::cout << "After selection sort n = " << n << std::endl;
    for(const auto& e: v) std::cout << e << ' ';
    std::cout << std::endl;
}