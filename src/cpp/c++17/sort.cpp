#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <random>
#include <fstream>

template <typename T>
static void print(const std::vector<int>& v, T& t) {
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>{t, ", "});
    t.write("\n", 1);
}

int main() {
    std::vector<int> v;
    std::random_device rd;
    std::default_random_engine e{rd()};
    std::uniform_int_distribution<int> dist{0, 15};
    std::ofstream of("output.txt");
    std::mt19937 g{rd()};

    for(int i = 0; i < 11; ++i) {
        v.push_back(dist(e));
    }


    print<std::ostream>(v, std::cout);
    std::cout << std::boolalpha << std::is_sorted(v.begin(), v.end()) << '\n';
    std::sort(v.begin(), v.end());
    std::cout << std::boolalpha << std::is_sorted(v.begin(), v.end())
              << ": ";
    print(v, of);

    // std::shuffle(v.begin(), v.end(), g);
    // std::cout << "after shuffle: ";
    // print(v);
    // std::partition(v.begin(), v.end(), [](int i){ return i < 5; });
    // std::cout << "after partition: ";
    // print(v);

    // std::shuffle(v.begin(), v.end(), g);
    // auto middle {std::next(v.begin(), int(v.size()) / 2)};
    // std::partial_sort(v.begin(), middle, v.end());
    // std::cout << "partial_sort: ";
    // print(v);

    // struct mystruct {
    //     int a;
    //     int b;
    // };

    // std::vector<mystruct> mv {
    //     {5, 100}, {1, 50}, {-123, 1000}, {3, 70}, {-10, 20}
    // };

    // std::sort(mv.begin(), mv.end(), [](const auto& lhs, const auto& rhs) {
    //     return lhs.a < rhs.a;
    // });

    // for(const auto& [a, b] : mv) {
    //     std::cout << "{" << a << ", " << b << "}\n";
    // }
}
