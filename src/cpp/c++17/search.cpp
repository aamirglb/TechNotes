#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <string>
#include <iterator>

struct city {
    std::string name;
    uint32_t    population;
};

bool operator==(const city& a, const city& b) {
    return a.name == b.name && a.population == b.population;
}

std::ostream& operator<<(std::ostream& os, const city& c) {
    return os << "{" << c.name << ", "
              << c.population << "}";
}

template <typename C>
static auto opt_print(const C& c) {
    return [end_itr{c.end()}](const auto& item) {
        if(item != end_itr) {
            std::cout << *item << '\n';
        } else {
            std::cout << "<end>\n";
        }
    };
}


static auto norm(int min, int max, int new_max) {
    const double diff (max - min);
    return [=](int val) {
        return static_cast<int>(((val - min) / diff * new_max));
    };
}

static auto clampval(int min, int max) {
    return [=](int val) -> int {
        return std::clamp(val, min, max);
    };
}

int main() {
    const std::vector<city> c {
        {"Aachen", 246000},
        {"Berlin", 3502000},
        {"Braunschweig", 251000},
        {"Cologne", 1060000}
    };

    auto print_city{ opt_print(c) };

    auto itr {std::find(c.begin(), c.end(), city{"Cologne", 1060000})};
    print_city(itr);

    auto itr2 {std::find_if(c.begin(), c.end(), [](const auto& item) {
        return item.name == "Cologne";
    })};
    print_city(itr2);

    auto population_more_than = [](uint32_t pop) {
        return [=](const city& item) {
            return item.population > pop;
        };
    };

    auto itr3 {std::find_if(c.begin(), c.end(), population_more_than(2000000))};
    print_city(itr3);

    std::vector<int> v;
    for(int i = 0; i < 11; ++i) v.push_back(i);
    auto print_int {opt_print(v)};

    auto [lower_itr, upper_itr] = std::equal_range(v.begin(), v.end(), 7);
    print_int(lower_itr);
    print_int(upper_itr);

    print_int(std::lower_bound(v.begin(), v.end(), 7));
    print_int(std::upper_bound(v.begin(), v.end(), 7));

    std::vector<int> v2 {1, 2, 3, 4, 4, 4, 8, 9, 10};
    auto [l, u] = std::equal_range(v2.begin(), v2.end(), 5);
    print_int(l);
    print_int(u);

    std::vector<int> v3 {0, 1000, 5, 250, 300, 800, 900, 321};
    const auto [min_itr, max_itr] = std::minmax_element(v3.begin(), v3.end());

    std::vector<int> v_norm;
    v_norm.reserve(v3.size());
    std::transform(v3.begin(), v3.end(), std::back_inserter(v_norm),
        norm(*min_itr, *max_itr, 255));

    std::copy(v_norm.begin(), v_norm.end(),
        std::ostream_iterator<int>{std::cout, ", "});
    std::cout << '\n';

    std::transform(v3.begin(), v3.end(), v_norm.begin(),
        clampval(0, 255));

    std::copy(v_norm.begin(), v_norm.end(),
        std::ostream_iterator<int>{std::cout, ", "});
    std::cout << '\n';
}