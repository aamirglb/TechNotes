#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <functional>

template <typename Itr>
static void print(Itr it, size_t chars) {
    std::copy_n(it, chars, std::ostream_iterator<char>{std::cout});
    std::cout << '\n';
}

int main() {
    const std::string long_string {
        "Lorem ipsum dolor sit amet, consetetur"
        " sadipscing elitr, sed diam nonumy eirmod"
    };
    const std::string needle {"elitr"};
    auto match {std::search(long_string.begin(), long_string.end(),
                            needle.begin(), needle.end())};

    print(match, 5);
}

