#include <iostream>
#include <ranges>
#include <cstddef>
#include <array>

int main() {
    auto ints = std::ranges::iota_view{1, 33};
    for(const auto& i : ints) {
        std::cout << i << ", ";
    }
    std::cout << std::endl;
    auto even_bytes = [](int i) { return (i % 8) == 0; };
    auto largest_value = [](int i){ return (1ULL << i) - 1; };

    for(unsigned long i : ints | std::views::filter(even_bytes) |
            std::views::transform(largest_value)) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;

    // test bytes
    // std::array<std::byte, 4> msg {
    //     42, 42, 42, 42
    // };
    std::byte b {42};
    std::array<std::byte, 2> msg {byte{42}, byte{43}};
}