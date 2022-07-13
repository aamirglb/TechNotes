#include <iostream>
#include <unordered_map>
#include <map>

// std::unordered_map<uint32_t, unsigned long long> memo;
std::map<uint32_t, unsigned long long> memo;

unsigned long long fib(uint32_t n)
{
    if(memo.find(n) != memo.end()) return memo[n];
    if(n <=2 ) return 1;

    memo[n] = fib(n-1) + fib(n-2);
    return memo[n];
}

int main()
{
    // std::cout << fib(4) << std::endl;
    // std::cout << fib(6) << std::endl;
    // std::cout << fib(8) << std::endl;
    // std::cout << fib(50) << std::endl;
    std::cout << "sizeof(unsigned long long): " << sizeof(unsigned long long) << std::endl;
    auto f = fib(150);
    std::cout << f << " " << std::hex << f << std::dec <<  std::endl;
    for(auto [key, value] : memo) {
        std::cout << key << ": " << value << std::endl;
    }
}