#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <numeric>

int main()
{
    std::vector<int> v(10);
    std::generate(v.begin(), v.end(), [](){ return rand() % 15;});

    for(auto &i : v) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::copy(v.begin(), v.end(),
        std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    int32_t a = 5, b = 10;
    std::cout << "GCD: " << std::gcd(a, b);

}