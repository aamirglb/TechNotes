#include <initializer_list>
#include <fmt/format.h>

using namespace std;

int sumIt(initializer_list<int> values) {
	int total{};
	for(auto v : values) total += v;
	return total;
}

int main() {
	int a { sumIt({1, 2, 3, 4, 5}) };
	int b { sumIt({60, 70, 80, 90, 100}) };
	fmt::print("a: {}\nb: {}\n", a, b);
}
