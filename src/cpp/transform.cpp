#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <list>
#include <functional>
#include <iterator>

using namespace std;
using namespace std::placeholders;

template <typename T>
inline void PRINT_ELEMENTS(const T& coll, const std::string& optcstr="")
{
    std::cout << optcstr;
    for(auto elem : coll) {
        std::cout << elem << ' ';
    }
    std::cout << std::endl;
}

int main()
{
    vector<int> v {1, 2, 3, 4, 5, 6, 7, 8, 9};
    list<int> lst;

    PRINT_ELEMENTS(v, "v: ");
    transform(v.cbegin(), v.cend(), v.begin(), negate<int>());
    PRINT_ELEMENTS(v, "v negated: ");

    transform(v.cbegin(), v.cend(), back_inserter(lst),
        bind(multiplies<int>(), _1, 10));
    PRINT_ELEMENTS(lst, "list: ");

    transform(lst.crbegin(), lst.crend(),
        ostream_iterator<int>(cout, " "),
        [](int elem){ return -elem; });
    cout << endl;
}