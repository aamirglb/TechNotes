#include <iostream>
#include <algorithm>
#include <vector>

bool doubled(int elem1, int elem2)
{
    return elem1 * 2 == elem2;
}
int main()
{
    std::vector<int> v{1, 3, 2, 4, 5, 5, 0, 6, 7, 7, 4};
    for(const auto &e : v) {
        std::cout << e << ' ';
    }
    std::cout << std::endl;

    auto pos = std::adjacent_find(v.begin(), v.end());
    if(pos != v.end()) {
        std::cout << "first two elements with equal value have position "
                  << std::distance(v.begin(), pos) + 1
                  << std::endl;
    }

    pos = std::adjacent_find(pos+1, v.end());
    if(pos != v.end()) {
        std::cout << "second two elements with equal value have position "
                  << std::distance(v.begin(), pos) + 1
                  << std::endl;
    }

    pos = std::adjacent_find(v.begin(), v.end(), doubled);
    if(pos != v.end()) {
        std::cout << "first two elements with second value twice the first "
                  << std::distance(v.begin(), pos) + 1 << std::endl;
    }
}