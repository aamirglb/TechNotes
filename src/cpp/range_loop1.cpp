#include <fmt/format.h>
#include <array>

using namespace std;

int main() {
	for(array arr{1, 2, 3, 4, 5}; auto i : arr)
		fmt::print("{}\n", i);
}
