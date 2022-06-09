#include <iostream>
#include <string>
#include <vector>
#include <ranges>
#include <algorithm>
#include <span>
#include <cassert>

template <typename T, std::size_t Sz>
void printSpan(std::span<T, Sz> sp)
{
    for(const auto& elem : sp) {
        std::cout << '"' << elem << "\" ";
    }
    std::cout << std::endl;
}

int main()
{
    std::vector<std::string> vec{"New York", "Tokyo", "Rio", "Berlin", "Sydney"};

    assert(vec.size() >= 3);

    std::span<const std::string, 3> sp3{vec.begin(), 3};
    std::cout << "first 3: ";
    printSpan(sp3);

    std::ranges::sort(vec);
    std::cout << "first 3 after sort(): ";
    printSpan(sp3);

    auto oldCapa = vec.capacity();
    vec.push_back("Cario");

    if(oldCapa != vec.capacity()) {
        sp3 = std::span<std::string, 3>{vec.begin(), 3};
    }
    std::cout << "first 3: ";
    printSpan(sp3);

    sp3 = std::span<std::string, 3>{vec.end() - 3, vec.end()};
    std::cout << "last 3: ";
    printSpan(sp3);

    std::cout << "vec: ";
    printSpan(std::span{vec});
}