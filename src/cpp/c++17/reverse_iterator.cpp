#define _GLIBCXX_DEBUG

#include <iostream>
#include <list>
#include <iterator>
#include <vector>

class cstring_iterator_sentinel {};

class cstring_iterator {
    const char *s {nullptr};
public:
    explicit cstring_iterator(const char *str) : s{str} {}
    char operator*() const { return *s; }
    cstring_iterator& operator++() {
        ++s;
        return *this;
    }
    bool operator!=(const cstring_iterator_sentinel) const {
        return s != nullptr && *s != '\0';
    }
};

class cstring_range {
    const char *s {nullptr};
public:
    cstring_range(const char *str) : s{str} {}
    cstring_iterator begin() const { return cstring_iterator{s}; }
    cstring_iterator_sentinel end() const { return {}; }
};

int main(int argc, char *argv[]) {
    std::vector<int> v{1, 2, 3};
    v.shrink_to_fit();
    const auto itr {v.begin()};
    std::cout << *itr << '\n';
    v.push_back(123);
    std::cout << *itr << '\n';
    return 0;

    std::list<int> lst{1, 2, 3, 4, 5};
    std::copy(lst.rbegin(), lst.rend(), std::ostream_iterator<int>{std::cout, ", "});
    std::cout << std::endl;
    std::copy(std::make_reverse_iterator(lst.end()),
             std::make_reverse_iterator(lst.begin()),
             std::ostream_iterator<int>{std::cout, " "});

    if(argc < 2) {
        std::cout << "Please provide one parameter.\n";
        return 1;
    }

    for(char c : cstring_range(argv[1])) {
        std::cout << c;
    }
    std::cout << std::endl;
}