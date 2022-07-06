#include <algorithm>
#include <iterator>
#include <list>
#include <vector>
#include <deque>
#include <set>
#include <iostream>

template <typename C>
void print(const C& c, const std::string& msg = "")
{
    std::cout << msg << ": ";
    for(auto const & e: c) std::cout << e << ' ';
    std::cout << std::endl;
}

int main()
{
    std::list<int32_t> coll1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<int32_t> coll2;

    std::copy(coll1.cbegin(), coll1.cend(),
              std::back_inserter(coll2));

    std::deque<int32_t> coll3;
    std::copy(coll1.cbegin(), coll1.cend(),
            std::front_inserter(coll3));

    std::set<int32_t> coll4;
    std::copy(coll1.cbegin(), coll1.cend(),
            std::inserter(coll4, coll4.end()));

    print(coll1, "coll1");
    print(coll2, "coll2");
    print(coll3, "coll3");
    print(coll4, "coll4");
}