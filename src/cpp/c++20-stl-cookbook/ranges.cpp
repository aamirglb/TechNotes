#include <iostream>
#include <format>
#include <ranges>
#include <vector>
#include <string>
#include <random>
#include <algorithm>

template <typename Container>
void print(Container c, std::string msg = {})
{
    std::cout << msg << ": ";
    for(auto n : c)
    {
        std::cout << n << ' ';
    }
    std::cout << '\n';
}

int main()
{
    const std::vector<int> nums{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto view1 = std::ranges::take_view(nums, 5);
    print(view1, "first 5");

    auto view2 = nums | std::ranges::views::take(13);
    print(view2, "first 13");

    auto view3 = nums | std::ranges::views::take(10) | std::ranges::views::reverse;
    print(view3, "reverse");

    auto view4 = nums | std::ranges::views::filter([](int i){ return i % 2 == 0; });
    print(view4, "even");

    auto view5 = nums | std::ranges::views::transform([](int i){ return i * i; });
    print(view5, "square");

    std::random_device rd;
    std::mt19937 engine{rd()};
    std::uniform_int_distribution d(1, 25);

    std::vector<int> v;
    for(int i = 0; i < 10; ++i) v.push_back(d(engine));
    print(v, "original vector");

    std::ranges::sort(v | std::ranges::views::reverse | std::ranges::views::drop(4));
    print(v, "sorted");


}