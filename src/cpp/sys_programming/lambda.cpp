#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

int main()
{
    std::vector<int> v {1, 2, 3, 4, 5, 6, 7, 8};
    std::for_each(std::begin(v), std::end(v),
        [](auto x) { std::cout << x << std::endl; });

    std::string prefix("0");
    std::for_each(std::begin(v), std::end(v),
        [&prefix](auto x) { std::cout << prefix << x << std::endl; });

    int x = 10;
    [&x]() mutable { x *= 2; }();
    std::cout << "x = " << x << std::endl;
}
