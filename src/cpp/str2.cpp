#include <fmt/format.h>
#include <charconv>
#include <string>
#include <string_view>

using namespace std;

double stringToDouble(string value) { 
	double number {0};
	from_chars(value.data(), value.data()+value.size(), number);
	return number;
}

int main() {
	fmt::print(stringToDouble("3.14572"));
}
