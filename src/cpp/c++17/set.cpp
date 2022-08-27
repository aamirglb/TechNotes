#include <iostream>
#include <set>
#include <iterator>
#include <string>

int main() {
    std::set<std::string> s;

    std::copy(std::istream_iterator<std::string>(std::cin),
        std::istream_iterator<std::string>(), std::inserter(s, s.begin()));
        // std::istream_iterator<std::string>(), std::inserter(s, s.end()));

    for(const auto &word : s) {
        std::cout << word << ", ";
    }
    std::cout << '\n';
}