#include <iostream>
#include <typeinfo>
#include <vector>
#include <list>
#include <map>

using namespace std::literals;

int main()
{
    std::vector v{2, 4, 6, 8}; // same as std::vector<int>
    std::list  d{1., 3., 5.};   // same as std::list<double>
    std::pair  p{"hi", "hello"};
    // std::map    m {
    //     {0, "zero"}
    // //     {1, "one"},
    // //     {2, "two"},
    // };
    std::cout << typeid(v[0]).name() << std::endl;
    std::cout << typeid(v).name() << std::endl;
}