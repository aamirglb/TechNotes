#include <iostream>
#include <format>
#include <concepts>

template <typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

template <typename T> requires Numeric<T>
T arg42(const T& arg)
{
    return arg+42;
}

template <typename T> requires Numeric<T>
struct Num
{
    T n;
    Num(T n) : n{n} {}
};

int main()
{
    const char* p = "7";
    std::cout << "result is: " << arg42(p) << '\n';
}