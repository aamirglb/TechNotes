#include <boost/format.hpp>
#include <boost/regex.hpp>

#include <iostream>

struct animal
{
    std::string name;
    int legs;
};

std::ostream &operator<<(std::ostream &os, const animal &a)
{
    return os << "[" << a.name << ", " << a.legs << "]";
}

int main()
{
    std::cout << boost::format{"%1%.%2%.%3%"} % 3 % 2 % 2023 << std::endl;
    std::cout << boost::format{"%1% %2% %1%"} % boost::io::group(std::showpos, 1) % 2 << std::endl;

    animal a{"cat", 4};
    std::cout << boost::format{"%1%"} % a << std::endl;

    std::string s{"Boost Libraries"};
    boost::regex expr{"(\\w+)\\s(\\w+)"};
    std::cout << std::boolalpha << boost::regex_match(s, expr) << std::endl;

    boost::smatch what;
    if (boost::regex_search(s, what, expr))
    {
        std::cout << what[0] << std::endl;
        std::cout << what[1] << "_" << what[2] << std::endl;
    }
}

// 108865
// 103210