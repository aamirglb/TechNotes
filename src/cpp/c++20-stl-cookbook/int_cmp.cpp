#include <utility>
#include <format>
#include <iostream>
#include <cstdio>

int main()
{
    int x{-3};
    unsigned y{7};
    if(x < y) std::puts("true");
    else std::puts("false");

    if(std::cmp_less(x, y)) std::puts("true");
    else std::puts("false");

    // auto t = std::make_unsigned_t<int>

    const int a{7};
    const int b{42};
    static_assert((a <=> b) < 0);
}