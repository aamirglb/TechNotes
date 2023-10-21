#include <iostream>
#include <format>
#include <span>

template <typename T>
void pspan(std::span<T> s)
{
    std::cout << std::format("Number of elements: {}\n", s.size());
    std::cout << std::format("Size of span: {}\n", s.size_bytes());
    for(auto e : s) std::cout << std::format("{} ", e);
    std::cout << std::endl;
}

int main()
{
    int carray[] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    pspan<int>(carray);
}