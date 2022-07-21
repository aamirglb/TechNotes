#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <iterator>
#include <algorithm>
#include <cstdlib>  // for abs
#include <functional>

bool isPrime(int32_t number)
{
    number = std::abs(number);

    if(number == 0 || number == 1) return false;

    int divisor;
    for(divisor = number/2; number % divisor != 0; --divisor);
    return divisor == 1;
}

int main()
{
    std::set<int32_t> s;
    std::vector<int32_t> v;

    for(int32_t i = 1; i < 11; ++i) s.insert(i);

    std::transform(s.begin(), s.end(),
        std::back_inserter(v),
        [](int32_t e){ return e*e; });

    std::copy(s.begin(), s.end(),
        std::ostream_iterator<int32_t>(std::cout, " "));
    std::cout << std::endl;
    std::copy(v.begin(), v.end(),
        std::ostream_iterator<int32_t>(std::cout, " "));
    std::cout << std::endl;

    std::transform(v.begin(), v.end(), v.begin(), std::negate<int32_t>());
    std::copy(v.begin(), v.end(),
        std::ostream_iterator<int32_t>(std::cout, " "));
    std::cout << std::endl;

    std::list<int32_t> l;

    for(int32_t i = 24; i <= 30; ++i) l.push_back(i);

    auto pos = std::find_if(l.begin(), l.end(), isPrime);
    if(pos != l.end()) {
        std::cout << *pos << " is first prime\n";
    } else {
        std::cout << "no prime in the range\n";
    }
}