#include "structbind.hpp"
#include <iostream>
#include <vector>

int main()
{
    Customer c{"Aamir", "Ali", 38};
    auto [f, l, v] = c;
    std::cout << "f/l/v: " << f << ' ' << l << ' ' << v << '\n';

    auto&& [f2, l2, v2] = c;
    std::string s = std::move(f2);
    f2 = "Mohd";
    v2 += 10;
    std::cout << "f2/l2/v2: " << f2 << ' ' << l2 << ' ' << v2 << '\n';

    std::cout << c.firstname() << ' '
              << c.lastname() << ' '
              << c.value() << '\n';

    // std::string s = std::move(f);
    // l = "Mohd";
    // v += 10;

    // std::cout << "f/l/v: " << f << ' ' << l << ' ' << v << '\n';
    // std::cout << c.getFirst() << ' '
    //           << c.getLast() << ' '
    //           << c.getValue() << '\n';
    // std::cout << "s: " << s << '\n';

    std::vector<Customer> cust {
        {"Aamir", "Ali", 30},
        {"Mohd", "Ali", 33},
        {"Umar", "Ali", 10},
    };

    for(const auto& [first, last, val] : cust) {
        std::cout << first << ' ' << last << ": " << val << '\n';
    }
}
