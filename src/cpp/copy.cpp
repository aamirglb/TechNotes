#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <list>
#include <string>

int main()
{
    std::vector<std::string> v1 { "Hello", "this", "is", "an", "example"};
    std::list<std::string> lst;

    std::copy(v1.cbegin(), v1.cend(), std::back_inserter(lst));

    std::copy(lst.cbegin(), lst.cend(),
        std::ostream_iterator<std::string>(std::cout, " "));
    std::cout << std::endl;

    std::copy(v1.crbegin(), v1.crend(), lst.begin());
    std::copy(lst.cbegin(), lst.cend(),
        std::ostream_iterator<std::string>(std::cout, " "));
    std::cout << std::endl;

    std::vector<char> v2(10, '.');
    for(int c='a'; c < 'f'; ++c) v2.push_back(c);
    v2.insert(v2.end(), 10, '.');
    for(const auto &c : v2) std::cout << c;
    std::cout << std::endl;

    std::vector<char> v3(v2.cbegin(), v2.cend());
    std::copy(v3.cbegin()+10, v3.cbegin()+16, v3.begin()+7);
    for(const auto &c : v3) std::cout << c;


}