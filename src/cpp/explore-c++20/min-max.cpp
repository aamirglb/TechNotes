#include <iostream>
#include <limits>

int main()
{
    int min{std::numeric_limits<int>::max()};
    int max{std::numeric_limits<int>::min()};
    bool any{false};
    int x;

#if 0
    while (std::cin >> x)
    {
        any = true;
        if (x < min)
            min = x;
        if (x > max)
            max = x;
    }
    if (any)
    {
        std::cout << "min = " << min << "\tmax = " << max << std::endl;
    }
#else
    int sum{};
    int count{};
    while (std::cin >> x)
    {
        sum += x;
        count += 1;
    }
    std::cout << "sum = " << sum << " count = " << count << " average = " << sum / count << '\n';
#endif
}