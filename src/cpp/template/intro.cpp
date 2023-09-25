#include <iostream>
#include <format>

class Foo
{
    int m_Value;
public:
    explicit Foo(const int i) : m_Value{i}
    {}

    explicit operator int() const { return m_Value; }
};

Foo operator+(const Foo& a, const Foo& b)
{
    return Foo(static_cast<int>(a) + static_cast<int>(b));
}

template <typename T>
T add(const T a, const T b)
{
    return a + b;
}

int main()
{
    auto a = add(10, 4);
    auto b = add<short>(55, 34);
    auto c = add<>(1., 4.5);

    std::cout << std::format("a={}, b={} c={}\n", a, b, c);
    // std::print("a={}, b={} c={}\n", a, b, c);

    auto d = add(Foo(3), Foo(4));
    std::cout << std::format("d={}\n", static_cast<int>(d));
}