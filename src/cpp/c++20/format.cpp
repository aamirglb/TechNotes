#include <format>
#include <string>
#include <iostream>

struct Frac
{
    long n;
    long d;
};

template<>
struct std::formatter<Frac> //: std::formatter<std::string>
{
    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return ctx.end();
    }

    template<typename FormatContext>
    auto format(const Frac& f, FormatContext& ctx)
    {
        return std::format_to(ctx.out(), "{0:d}/{1:d}", f.n, f.d);
    }
};

int main()
{
    int v{10};
    std::string s{"Hello"};

    std::cout << std::format("{}, {}\n", v, s);
    // std::print( std::format("{}, {}\n", v, s));

    std::cout << std::format("{:.<10}\n", v);
    std::cout << std::format("{:.>10}\n", v);
    std::cout << std::format("{:.^10}\n", v);

    Frac f{5, 3};
    std::cout << std::format("Frac: {}\n", f);
}