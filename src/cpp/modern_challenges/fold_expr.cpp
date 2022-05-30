#include <iostream>
#include <iterator>
#include <vector>
#include <list>

template<typename C, typename... Args>
void push_back(C& c, Args&&... args)
{
    (c.push_back(args), ...);
}

int main()
{
    std::vector<int32_t> v;
    push_back(v, 1, 2, 3, 4, 5);
    std::copy(std::begin(v), std::end(v),
        std::ostream_iterator<int32_t>(std::cout, " "));
    std::cout << std::endl;

    std::list<int32_t> l;
    push_back(l, 10, 9, 8, 7, 6, 4);
    std::copy(std::begin(l), std::end(l),
        std::ostream_iterator<int32_t>(std::cout, " "));
    std::cout << std::endl;
}