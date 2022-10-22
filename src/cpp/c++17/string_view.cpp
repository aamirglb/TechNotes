#include <iostream>
#include <string>
#include <string_view>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std::string_literals;
using namespace std::literals::string_view_literals;

std::string trim_whitespace_surrounding(const std::string &s) {
    const char whitespace[] {" \t\n"};
    const size_t first {s.find_first_not_of(whitespace)};
    if(std::string::npos == first) return {};

    const size_t last {s.find_last_not_of(whitespace)};
    return s.substr(first, (last - first + 1));
}

int main() {
    std::string a {"a"};
    auto b ("b"s);

    std::string_view c {"c"};
    auto             d {"d"sv};

    std::cout << a << ", " << b << std::endl;
    std::cout << c << ", " << d << std::endl;

    std::ostringstream o;
    o << a << " " << b << " " << c << " " << d;
    auto con {o.str()};
    std::cout << con << std::endl;

    std::transform(con.begin(), con.end(), con.begin(), ::toupper);
    std::cout << con << std::endl;

    std::string s {" \t\n string surrounded by "
                   "whitespace \t\n "};
    std::cout << "{" << s << "}\n";
    std::cout << "{" << trim_whitespace_surrounding(s) << "}\n";
}