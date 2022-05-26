#include <array>
#include <span>
#include <vector>
#include <iostream>

void print(std::span<int> container)
{
    for(const auto &e : container)
        std::cout << e << " - ";
    std::cout << "\n\n";
}

int main()
{
    std::vector<int> v {2, 1, 5, 8, 3, 4};
    int elems[]{2, 4, 6, 8, 10};
    std::array<int, 5> arr {3, 6, 9, 12, 15};
    
    print(elems);
    print(v);
    print(arr);
}