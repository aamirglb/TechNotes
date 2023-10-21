#include <iostream>
#include <concepts>

template <typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

template <typename T> requires Numeric<T>
T arg42(const T& arg)
{
    return arg + 42;
}

int main()
{
    std::cout << arg42(1) << std::endl;
}