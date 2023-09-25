#include <iostream>
#include <string>
#include <vector>

union S
{
    std::string str;
    std::vector<int> vec;
    ~S() {}
};

int main()
{
    // S empty;
    S s{"Hello, world"};
    std::cout << "s.str = " << s.str << std::endl;
    s.str.~basic_string<char>();

    new (&s.vec) std::vector<int>;
    s.vec.push_back(10);
    std::cout << s.vec.size() << std::endl;
}