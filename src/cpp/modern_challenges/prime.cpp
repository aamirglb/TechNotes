#include <iostream>
#include <vector>
#include <limits>
bool is_prime(const uint64_t num)
{

    if(num <= 3) { std::cout << num << " "; return num > 1; }
    for(auto i = 4; i < num; ++i) {
        if(num % i == 0) {
            return false;
        }
    }

    return true;
}
int main()
{
    std::cout << "Enter number of primes to find: ";
    uint64_t prime_count;
    std::cin >> prime_count;

    std::vector<uint64_t> primes;
    for(decltype(prime_count) i = 0; i < /*std::numeric_limits<uint64_t>::max()*/500; ++i) {
        if(is_prime(i)) {
            primes.push_back(i);
            if(primes.size() == prime_count)
                break;
        }
    }

    for(auto prime : primes) {
        std::cout << prime << std::endl;
    }
}