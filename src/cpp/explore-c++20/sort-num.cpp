#include <algorithm>
#include <vector>
#include <iostream>
#include <iterator>
#include <ranges>

int main()
{
    std::vector<int> data;
    std::ranges::copy(std::ranges::istream_view<int>(std::cin), std::back_inserter(data));
    std::ranges::reverse(data);
    std::ranges::copy(data, std::ostream_iterator<int>(std::cout, "\n"));
    // std::vector<int> data{};
    // int x{};

    // while (std::cin >> x)
    // {
    //     data.emplace_back(x);
    // }

    // std::ranges::sort(data);
    // for (int ele : data)
    // {
    //     std::cout << ele << '\n';
    // }
}