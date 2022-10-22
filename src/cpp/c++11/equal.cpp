#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v{ 1, 2, 3, 2, 1};
    return std::equal(v.begin(), v.begin() + v.size()/2, v.rbegin());
}