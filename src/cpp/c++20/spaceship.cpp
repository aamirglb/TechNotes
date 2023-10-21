#include <iostream>
#include <compare>

struct Num
{
    int a;
    constexpr bool operator==(const Num& rhs) const
    {
        return a == rhs.a;
    }

    constexpr bool operator!=(const Num& rhs) const
    {
        return !( a == rhs.a );
    }

    constexpr bool operator<(const Num& rhs) const
    {
        return a < rhs.a;
    }

    constexpr bool operator>(const Num& rhs) const
    {
        return rhs.a < a;
    }

    constexpr bool operator<=(const Num& rhs) const
    {
        return !(rhs.a < a);
    }

    constexpr bool operator>=(const Num& rhs) const
    {
        return !( a < rhs.a);
    }
};

struct Number
{
    int a;
    constexpr Number(int a) : a{a} {}
    auto operator<=>(const Number&) const = default;
};

struct Frac
{
    long n;
    long d;

    constexpr Frac(int a, int b) : n{a}, d{b} {}
    constexpr double dbl() const
    {
        return static_cast<double>(n) / static_cast<double>(d);
    }
    constexpr auto operator<=>(const Frac& rhs) const
    {
        return dbl() <=> rhs.dbl();
    }

    constexpr auto operator==(const Frac& rhs) const
    {
        return dbl() <=> rhs.dbl() == 0;
    }
};

constexpr Number a{7};
constexpr Number b{7};
constexpr Number c{42};

constexpr Frac aa(10, 15);
constexpr Frac bb(2, 3);
constexpr Frac cc(5, 3);

int main()
{
    static_assert(a < c);
    static_assert(c > a);
    static_assert(a == b);
    static_assert(a <= b);
    static_assert(a <= c);
    static_assert(c >= a);
    static_assert(a != c);

    static_assert(cc > aa);
    static_assert(aa == bb);
    static_assert(aa <= bb);
    static_assert(aa <= cc);
    static_assert(cc >= aa);
    static_assert(aa != cc);

    puts("done.");
}