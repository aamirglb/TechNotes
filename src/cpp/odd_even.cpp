#include <vector>
#include <fmt/format.h>

using namespace std;

struct OddsAndEvens {
	vector<int> odds;
	vector<int> evens;
};

OddsAndEvens splitArray(const vector<int>& arr) {
	vector<int> odds, evens;
	for(auto i : arr) {
		if(i % 2) odds.push_back(i);
		else evens.push_back(i);
	}
	return OddsAndEvens{ .odds = odds, .evens = evens };
}

int main() {
	vector<int> original {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
	auto oddsAndEvens { splitArray(original) };

	for(const auto i : original) {
		fmt::print("{}, ", i);
	}
	fmt::print("\n");
	
	fmt::print("odds: ");
	for(const auto i : oddsAndEvens.odds) {
		fmt::print("{}, ", i);
	}
	fmt::print("\n");

	fmt::print("evens: ");
	for(const auto i : oddsAndEvens.evens) {
		fmt::print("{}, ", i);
	}
	fmt::print("\n");
}
