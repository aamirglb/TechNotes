// quick sort algorithm

#include <iostream>
#include <vector>
#include <random>
#include <string>

int32_t partition(std::vector<int32_t> &v, int32_t low, int32_t high) {
    int32_t pivot = v[low];
    int32_t i = low, j = high;

    do {
        do { ++i; } while(v[i] <= pivot);
        do { --j; } while(v[j] > pivot);

        if(i < j) std::swap(v[i], v[j]);
    } while(i < j);

    std::swap(v[low], v[j]);
    return j;
}

void quickSort(std::vector<int32_t> &v, int32_t low, int32_t high) {
    int32_t j;
    if(low < high) {
        j = partition(v, low, high);
        quickSort(v, low, j);
        quickSort(v, j+1, high);
    }
}

int main(int argc, char *argv[]) {
    int32_t n = 10;
    if(argc > 1) {
        n = std::stoi(argv[1]);
    }

    // generate n random numbers
    std::random_device d;
    std::default_random_engine e(d());
    std::uniform_int_distribution dt(-10, 40);

    std::vector<int32_t> v(n);
    for(size_t i = 0; i < n; ++i) {
        v[i] = dt(e);
    }

    std::cout << "Before sort: \n";
    for(const auto &e : v) std::cout << e << ' ';
    std::cout << std::endl;

    quickSort(v, 0, n-1);

    std::cout << "After quick sort: \n";
    for(const auto &e : v) std::cout << e << ' ';
    std::cout << std::endl;
}