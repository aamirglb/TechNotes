#include <iostream>
#include <vector>
#include <map>
#include <ranges>

int main()
{
    namespace vws = std::views;

    std::map<std::string, int> composers {
        {"Bach", 1685},
        {"Mozart", 1756},
        {"Beethoven", 1770},
        {"Tchaikovsky", 1840},
        {"Chopin", 1810},
        {"Vivaldi", 1678},
    };

    for(const auto& elem : composers
            | vws::filter([](const auto& y) {
                    return y.second >= 1700;
                })
            | vws::take(3)
            | vws::keys
    ) {
        std::cout << "- " << elem << '\n';
    }
}