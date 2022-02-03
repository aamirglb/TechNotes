#include <fmt/format.h>
#include <limits>

int main() {
	using namespace std;
	fmt::print("int limits:\n");

	fmt::print("Max int: {0:#x}\n", numeric_limits<int>::max());
	fmt::print("Min int: {0:#x}\n", numeric_limits<int>::min());
	fmt::print("Lowest int: {}\n", numeric_limits<int>::lowest());

	fmt::print("double limits:\n");
	fmt::print("Max double: {}\n", numeric_limits<double>::max());
	fmt::print("Min double: {}\n", numeric_limits<double>::min());
	fmt::print("Lowest double: {}\n", numeric_limits<double>::lowest());

	fmt::print("Infinity: {}\n", numeric_limits<double>::infinity());
}
	
