#include "Array.hpp"
#include <limits>

int main()
{
    Array<int> data{10};
    for(size_t i{}; i < data.size(); ++i) {
        data[i] = i*2;
    }
    std::cout << data;

    std::cout << std::numeric_limits<unsigned long long>::max() << std::endl;
    std::cout << std::numeric_limits<double>::max() << std::endl;
}