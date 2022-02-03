#include <fmt/format.h>

constexpr /*consteval*/ double inchToMm(double inch) { return inch * 25.4; }
constexpr double const_inch { 6.0 };
constexpr double mm1 { inchToMm(const_inch) };

double dynamic_inch { 8.0 };
double mm2 { inchToMm(dynamic_inch) };


int main() {
	fmt::print("mm1: {}\n", mm1);
	fmt::print("mm2: {}\n", mm2);
}
