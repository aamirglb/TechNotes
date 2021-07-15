#include <iostream>
#include <set>
#include <algorithm>
#include <iterator>
#include <vector>

int main() {
    std::set<int32_t> s1 = {1, 2, 4, 6, 8, 9 };
    std::set<int32_t> s2 = {1, 3, 4, 5, 6, 7, 8, 9 };
    std::vector<int32_t> v;
    std::set_difference(s1.begin(), s1.end(),
                        s2.begin(), s2.end(),
                        std::back_inserter(v));
    std::cout << "v.size: " << v.size() << '\n';

    v.clear();
    std::set_difference(s2.begin(), s2.end(),
                        s1.begin(), s1.end(),
                        std::back_inserter(v));
    std::cout << "v.size: " << v.size() << '\n';
}