#include <iostream>
#include <format>

template <int N>
int fib = fib<N-1> + fib<N-2>;

template<>
int fib<2> = 1;

template <>
int fib<1> = 1;

int main()
{
    std::cout << std::format("fib<4> = {}\n", fib<4>);
    std::cout << std::format("fib<5> = {}\n", fib<5>);
    std::cout << std::format("fib<6> = {}\n", fib<6>);
}