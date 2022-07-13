#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main()
{
    std::vector<int32_t> A = {15,-2,2,-8,1,7,10,23};
    int32_t N = 8;

    auto total = std::accumulate(A.begin(), A.end(), 0);
    std::cout << total << std::endl;

    for(size_t i = N-1; i > 0; --i) {
        std::cout << std::accumulate(A.begin(), A.begin()+i, 0) << "\n";
    }
}