// Bubble sort algorithm
#include <iostream>
#include <vector>
#include <random>


void bubbleSort(std::vector<int32_t> &v) {
    bool isAlreadySorted {true}; // to make it adaptive
    // pass loop
    size_t n = v.size();
    for(size_t pass = 0; pass < n-1; ++pass) {
        for(size_t j = 0; j < n-1-pass; ++j) {
            if(v[j] > v[j+1]) {
                isAlreadySorted = false;
                std::swap(v[j], v[j+1]);
            }
        }
        if(isAlreadySorted) {
            return;
        }
    }
}

// secure system labrotary
int main()
{
    std::random_device d;
    std::default_random_engine e(d());
    std::uniform_int_distribution<int32_t> value(0, 50);
    std::vector<int32_t> v;
    for(int32_t i = 0; i < 10; ++i) {
        v.push_back(value(e));
    }
    std::cout << "Before Sort: ";
    for(const auto& e: v) std::cout << e << ' ';
    std::cout << std::endl;

    bubbleSort(v);
    std::cout << "After Sort: ";
    for(const auto& e: v) std::cout << e << ' ';
    std::cout << std::endl;

}