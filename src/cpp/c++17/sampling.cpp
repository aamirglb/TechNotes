#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
#include <map>
#include <iomanip>

int main() {
    constexpr size_t data_points {100000};
    constexpr size_t sample_points {100};

    constexpr int32_t mean{10};
    constexpr size_t  dev{3};

    std::random_device rd;
    std::mt19937       gen{rd()};
    std::normal_distribution<> d {mean, dev};

    std::vector<int> v;
    v.reserve(data_points);
    std::generate_n(std::back_inserter(v), data_points, [&]{ return d(gen); });
    // for(const auto& e : v) std::cout << e << ' ';

    std::vector<int> samples;
    samples.reserve(sample_points);
    std::sample(v.begin(), v.end(), std::back_inserter(samples),
        sample_points, std::mt19937{std::random_device{}()});

    std::map<int, size_t> hist;
    for(const auto& e : samples) ++hist[e];

    for(const auto& [value, count] : hist) {
        std::cout << std::setw(2) << value << " "
                  << std::string(count, '*') << '\n';
    }
}
