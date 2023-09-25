#include <iostream>
#include <fmt/core.h>

///////////////////////////////////////////
// 32-bit floating point layout
// 31 bit     - sign bit
// 23-30 bits - 8-bit exponent
// 0-22 bits  - 23-bit fraction
///////////////////////////////////////////

union SuperFloat
{
    float f;
    int i;
};

int raw_mantissa(SuperFloat f)
{
    return f.i & ((1 << 23) - 1);
}

int raw_exponent(SuperFloat f)
{
    return (f.i >> 23) & 0xFF;
}

int main()
{
    SuperFloat f1;
    f1.f = 0.15625;

    std::cout << fmt::format("Exponent: {} - {:x}, Fraction: {} - {:x}",
                             raw_exponent(f1),
                             raw_exponent(f1),
                             raw_mantissa(f1),
                             raw_mantissa(f1))
              << std::endl;
}