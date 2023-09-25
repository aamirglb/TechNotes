#include <iostream>
#include <format>
#include <compare>
#include <version>

struct Num
{
    int a;

    constexpr bool operator==(const Num& rhs) const { return a == rhs.a; }
    constexpr bool operator!=(const Num& rhs) const { return !(a==rhs.a); }
    constexpr bool operator< (const Num& rhs) const { return a < rhs.a; }
    constexpr bool operator> (const Num& rhs) const { return rhs.a < a; }
    constexpr bool operator<=(const Num& rhs) const { return !(rhs.a < a); }
    constexpr bool operator>=(const Num& rhs) const { return !(a < rhs.a); }
};

struct NumV2
{
    int a;
    constexpr NumV2(int a) : a{a} {}
    auto operator<=>(const NumV2&) const = default;
};

struct Fraction
{
    long n;
    long d;

    constexpr Fraction(int a, int b) : n{a}, d{b} {}
    constexpr double dbl() const {
        return static_cast<double>(n) / static_cast<double>(d);
    }

    // = default; will not work since member are not stand-alone scalar
    constexpr auto operator<=>(const Fraction& rhs) const {
        return dbl() <=> rhs.dbl();
    }

    // 'expression rewrite' rule will not rewrite == and != with custom operator<=>
    constexpr auto operator==(const Fraction& rhs) const {
        return dbl() <=> rhs.dbl() == 0;
    }
};

int main()
{
    constexpr NumV2 a{7};
    constexpr NumV2 b{7};
    constexpr NumV2 c{42};

    static_assert(a < c);
    static_assert(c > b);
    static_assert(a == b);
    static_assert(a <= b);
    static_assert(a <= c);
    static_assert(c >= a);
    static_assert(a != c);

    constexpr Fraction a1(10, 15);
    constexpr Fraction b1(2, 3);
    constexpr Fraction c1(5, 3);

    static_assert(a1 < c1);
    static_assert(c1 > a1);
    static_assert(a1 == b1);
    static_assert(a1 <= b1);
    static_assert(a1 <= c1);
    static_assert(c1 >= a1);
    static_assert(a1 != c1);

    std::cout << std::endl;
    #ifdef __cpp_lib_three_way_comparison
        std::cout << "value is " << __cpp_lib_three_way_comparison << std::endl;
    #endif
    
    std::cout << "All good!!\n";
}