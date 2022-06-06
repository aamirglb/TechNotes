#include <iostream>
#include <iomanip>

int main()
{
    std::initializer_list<double> values {
        0x1p4,       // 16
        0xA,         // 10
        0xAp2,       // 40
        5e0,         // 5
        0x1.4p+2,    // 5
        1e5,         // 100000
        0x1.86Ap+16, // 100000 1 + (86A/16^3) * 2^16
        0xC.68p+2,   // 49.625
    };

    for(double d : values) {
        std::cout << "dec: " << std::setw(6) << std::defaultfloat << d
                  << " hex: " << std::hexfloat << d << '\n';
    }
}
