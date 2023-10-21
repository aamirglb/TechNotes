#include <iostream>
#include <format>

template <typename Input, typename Predicate>
int count_if(Input start, Input end, Predicate p)
{
    int total{};
    for(Input i = start; i != end; ++i)
    {
        if(p(*i)) ++total;
    }
    return total;
}

int main()
{
    int arr[]{1, 1, 2, 3, 4, 5, 8, 11};
    int odds = count_if(std::begin(arr), std::end(arr), 
        [](const int n){ return n % 2 == 1; });
    std::cout << std::format("odd number = {}\n", odds);
}