#include <vector>
#include <algorithm>
#include <ranges>
#include <iostream>

namespace rng = std::ranges;

void print(const auto& col) {
    for(const auto& elem : col) {
        std::cout << elem << ' ';
    }
    std::cout << std::endl;
}

int main()
{
    std::vector<int32_t> col{5, 4, 9, 0, 7, 2, 3};
    std::vector<std::string> cities{"Rio", "Tokyo", "New York", "Berlin"};
    rng::sort(col);
    rng::sort(cities);

    print(cities);
    rng::sort(cities[0]);
    print(cities[0]);

    for(const auto &elem : col)
        std::cout << elem << ' ';
    std::cout << std::endl;

    for(const auto& elem : std::views::take(cities, 3))
        std::cout << elem << std::endl;

    for(int val : std::views::iota(0, 11)) {
        std::cout << val << ' ';
    }
    std::cout << std::endl;

    std::vector<int32_t> v;
    for(int i = 0; i < 13; ++i) v.push_back(i);

    auto v2 = v
        | std::views::filter([](auto elem){ return elem % 3 == 0; })
        | std::views::transform([](auto elem) { return elem * elem; })
        | std::views::take(3);

    print(v);
    for(const auto& elem : v2) std::cout << elem << std::endl;
    // print(v2);
}