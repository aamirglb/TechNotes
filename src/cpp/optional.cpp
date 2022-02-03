#include <iostream>
#include <fmt/format.h>

using namespace std;

optional<int> getData(bool giveIt) {
	if(giveIt) {
		return 42;
	}
	return nullopt;
}

int main() {
	optional<int> data1{ getData(true) };
	optional<int> data2{ getData(false) };

	fmt::print("data1.has_value = {}\n", data1.has_value());
	fmt::print("data2.has_value = {}\n", data2.has_value());
	
	if(data1) {
		fmt::print("data1 has value.\n");
	}

	fmt::print("data1.value = {}\n", data1.value());
	fmt::print("data2.value = {}\n", *data2); // reading value if no value is available is undefined
	fmt::print("value_or() data2.value = {}\n", data2.value_or(15));
}
