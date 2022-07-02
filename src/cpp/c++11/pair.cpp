#include <utility>
#include <iostream>
#include <tuple>
#include <functional>
#include <iomanip>
#include <vector>

template<typename T1, typename T2>
std::ostream& operator << (std::ostream& os,
                            const std::pair<T1, T2>& p)
{
    return os << "[" << p.first << ", " << p.second << "]";
}

class Foo
{
public:
    Foo(std::tuple<int, float>) {
        std::cout << "Foo:Foo(tuple)" << std::endl;
    }

    // Foo(int a, float b) {
    //     std::cout << "Foo::Foo(int, float)" << std::endl;
    // }
    template<typename... Args>
    Foo(Args... args) {
        std::cout << "Foo::Foo(args...)" << std::endl;
    }
};

uint64_t fib(uint64_t n) {
    if(n <= 1) return n;
    return fib(n-2) + fib(n-1);
}

uint64_t fib_memoization(int32_t n)
{
    static std::vector<uint64_t> results(n+1, -1);
    if(n <= 1) {
        results[n] = n;
        return n;
    } else {
        if(results[n-2] == -1) {
            results[n-2] = fib_memoization(n-2);
        }
        if(results[n-1] == -1) {
            results[n-1] = fib_memoization(n-1);
        }
    }
    return results[n-2] + results[n-1];
}

int main()
{
    std::pair<int32_t, double> p1 = std::make_pair(11, 3.1425);
    std::cout << p1 << std::endl;

    std::cout << std::get<0>(p1) << " " << std::get<1>(p1) << std::endl;
    std::cout << std::tuple_size<std::pair<int32_t, double>>::value << std::endl;
    // std::cout << std::tuple_element<0, std::pair<int32_t, double>>::type << std::endl;
    //           << std::tuple_element<1, std::pair<int32_t, double>>::type << std::endl;

    std::tuple<int, float> t(1, 3.1452);
    std::pair<int, Foo> p2(42, t);
    std::pair<int, Foo> p3(std::piecewise_construct, std::make_tuple(42), t);

    {
        int i = 0;
        auto p = std::make_pair(std::ref(i), std::ref(i));
        ++p.first;
        ++p.second;

        std::cout << "i: " << i << std::endl;
    }

    char c = 'a';
    {
        std::pair<char, char> p = std::make_pair('x', 'y');
        std::tie(std::ignore, c) = p;
        ++p.first;
    }
    std::cout << "c: " << c << std::endl;
    // uint64_t r = fib(50);
    // std::cout << "Fib(7): " << r << " " << std::hex << r << std::dec << std::endl;
    uint64_t r = fib_memoization(70);
    std::cout << r << " " << std::hex << r << std::endl;
}