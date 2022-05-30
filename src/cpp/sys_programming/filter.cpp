#include <vector>
#include <iostream>
#include <ranges>
#include <algorithm>
#include <tuple>
#include <iomanip>

template <typename T,
          typename TIter = decltype(std::begin(std::declval<T>())),
          typename = decltype(std::end(std::declval<T>()))>
constexpr auto enumerate(T && iterable)
{
    struct iterator
    {
        size_t i;
        TIter iter;
        bool operator != (const iterator & other) const { return iter != other.iter; }
        void operator ++ () { ++i; ++iter; }
        auto operator * () const { return std::tie(i, *iter); }
    };
    struct iterable_wrapper
    {
        T iterable;
        auto begin() { return iterator{ 0, std::begin(iterable) }; }
        auto end() { return iterator{ 0, std::end(iterable) }; }
    };
    return iterable_wrapper{ std::forward<T>(iterable) };
}

int main()
{
    // std::vector<int> temperatures {15, -6, 25, -3, 0, -1, 21, 15};
    std::vector<int> temperatures {28, 25, -8, -3, 15, 21, -1};
    auto minus = [](int i) { return i>=0; };
    auto toFahrenheit = [](int i){ return (i*(9./5.)) + 32; };

    for(auto i : temperatures 
        | std::views::filter(minus) 
        | std::views::transform(toFahrenheit))
        std::cout << i << ' ';

    std::vector<int> v(120);
    std::generate(std::begin(v), std::end(v), [](){ return rand() % 100; });

    std::cout << "\n\nRandom Numbers...\n";
    for(auto [i, e] : enumerate(v)) {
        if( (i+1) % 10 != 0 ) {
            std::cout << std::setw(2) << e << ", ";
        } else {
            std::cout << e << "\n";
        }
    } 
    std::cout << "\n";
}