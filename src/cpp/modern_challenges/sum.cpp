#include <iostream>

int main()
{
    std::cout << "Enter limit: ";
    int32_t limit {};
    std::cin >> limit;
    uint64_t sum {};

    for(auto i = 3; i <= limit; ++i)
    {
        if(i % 3 == 0 || i % 5 == 0) sum += i;
    }

    std::cout << "Sum = " << sum << std::endl;
}