#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <cassert>

void insert_sorted(std::vector<std::string>& v, const std::string& word) {
    const auto itr = std::lower_bound(v.begin(), v.end(), word);
    v.insert(itr, word);
}

int main() {
    std::vector<std::string> v {
        "some", "random", "words", "without", "order",
        "aaa", "yyy",
    };

    assert(false == std::is_sorted(v.begin(), v.end()));
    std::sort(v.begin(), v.end());
    assert(true == std::is_sorted(v.begin(), v.end()));

    insert_sorted(v, "foobar");
    insert_sorted(v, "zzz");

    for(const auto &w : v) {
        std::cout << w << '\n';
    }
}