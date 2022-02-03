// g++ -Wall -std=c++17 -I ./include -DFMT_HEADER_ONLY hex_float.cpp 
#include <iostream>
#include <fmt/format.h>
#include <cstddef>

int main() {
	// 0.3 hex, 3 * 16^-1 => (3/16) multiplied by 2^10
	// 3 * 1024 / 16
	double d1 = 0xA.Bp5;
	double d2 = 0xb.cp2;
	double d3 = 0x3.ABCp-10;

	fmt::print("d1: {}, d2: {}, d3: {}\n", d1, d2, d3);

	std::byte b {42};
	fmt::print("b: {}\n", b);
}
