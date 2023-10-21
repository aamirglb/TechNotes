#include <iostream>
#include <format>
#include <vector>

template<typename T>
const char* f(const T a)
{
    return typeid(T).name();
}

void printc(auto& c)
{
    std::cout << std::format("size({}) ", c.size());
    for(auto& e: c)
    {
        std::cout << std::format("{} ", e);
    }
    std::cout << std::endl;
}

int main()
{
    using namespace std::string_literals;
    std::cout << std::format("T is {}\n", f(47));
    std::cout << std::format("T is {}\n", f(47L));
    std::cout << std::format("T is {}\n", f(47.));
    std::cout << std::format("T is {}\n", f("47"));
    std::cout << std::format("T is {}\n", f("47"s));

    std::cout << std::endl;
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    printc(v);

    std::erase(v, 4);
    printc(v);
}