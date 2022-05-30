#include <iostream>
#include <string>
#include <vector>

template<typename T>
T minimum(const T a, const T b) {
    return a < b ? a : b;
}

template<typename T1, typename... T>
T1 minimum(T1 a, T... args) {
    return minimum(a, minimum(args...));
}

template<class Compare, typename T>
T min_with_compare(Compare comp, const T a, const T b)
{
    return comp(a, b) ? a : b;
}

template<class Compare, typename T1, typename... T>
T1 min_with_compare(Compare comp, T1 a, T... args)
{
    return min_with_compare(comp, a, min_with_compare(comp, args...));
}

template<typename T>
class Test
{
public:
    Test() : _data{} {}
    explicit Test(T data) : _data{data}{}

    friend bool operator<(const Test a, const Test b) {
        return a._data < b._data;
    }

    friend bool operator>(const Test a, const Test b) {
        return !(a < b);
    }

    friend std::ostream& operator<<(std::ostream& os, const Test a) {
        os << a._data;
        return os;
    }

private:
    T _data;
};

int main()
{
    auto x = minimum(3, 7, 8, 1, 9, 4);
    std::cout << "min = " << x << std::endl;

    auto y = min_with_compare(std::less<>(), 4, 5, 2, 6, 7);
    auto z = min_with_compare(std::greater<>(), 4, 5, 2, 6, 7);
    std::cout << "y = " << y << std::endl;
    std::cout << "z = " << z << std::endl;

    Test t1{5}, t2{3}, t3{2}, t4{10};
    auto t = min_with_compare(std::less<>(), t1, t2, t3, t4);
    std::cout << "min = " << t << std::endl;

    t = min_with_compare(std::greater<>(), t1, t2, t3, t4);
    std::cout << "max = " << t << std::endl;

    Test<std::string> s1{"hello"}, s2{"world"}, s3{"c++"}, s4{"templates"};
    auto s = min_with_compare(std::less<>(), s1, s2, s3, s4);
    std::cout << "min = " << s << std::endl;

    s = min_with_compare(std::greater<>(), s1, s2, s3, s4);
    std::cout << "max = " << s << std::endl;

    // test end of file marker
    std::cout << "Enter integers followed by EOF (Ctrl-D>\n";
    std::vector<int32_t> v;
    for(int32_t i ; std::cin >> i;)
        v.push_back(i);
    for(const auto i : v) std::cout << i << " ";
    std::cout << std::endl;
}
