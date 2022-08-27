#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <tuple>
#include <iterator>
#include <algorithm>

namespace std {
    std::ostream& operator<<(std::ostream& os, const std::pair<int, std::string> &p) {
        return os <<"(" << p.first << ", " << p.second << ")";
    }
}

int main() {
    std::vector<std::pair<int, std::string>> v {
        {1, "one"},
        {2, "two"},
        {3, "three"},
        {4, "four"},
        {5, "five"},
    };

    std::map<int, std::string> m;
    std::copy_n(v.begin(), 3, std::inserter(m, m.begin()));
    auto shell_itr {std::ostream_iterator<std::pair<int, std::string>>{std::cout, ", "}};
    std::copy(m.begin(), m.end(), shell_itr);
    std::cout << '\n';
    m.clear();
    std::move(v.begin(), v.end(), std::inserter(m, m.begin()));
    std::copy(m.begin(), m.end(), shell_itr);
    std::cout << '\n';
    std::copy(v.begin(), v.end(), shell_itr);
    std::cout << '\n';
}
