#include <format>
#include <string_view>
#include <cstdio>
#include <numbers>

template <typename ... Args>
void print(const std::string_view fmt_str, Args&&... args)
{
    auto fmt_args{ std::make_format_args(args...)};
    std::string outstr{ std::vformat(fmt_str, fmt_args)};
    std::fputs(outstr.c_str(), stdout);
}

struct Fraction
{
    long n;
    long d;
};

template <>
struct std::formatter<Fraction>
{
    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(const Fraction& f, FormatContext& ctx) const
    {
        return format_to(ctx.out(), "{0:d}/{1:d}", f.n, f.d);
    }
};

int main()
{
    std::string who{"aamir"};
    int ival{42};

    print("Hello, {}\n", who);
    print("pi: {}\n", std::numbers::pi);
    print("Hello {1} {0}\n", ival, who);
    print("{:.^10}\n", ival);
    print("{:.5}\n", std::numbers::pi);

    print("\n");

    Fraction f{5, 3};
    print("Frac: {}\n", f);
}
