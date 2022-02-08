#include <fmt/format.h>
#include <vector>

using namespace std;

int main() {
	vector<int> v;
	auto prev_caps = v.capacity();
	fmt::print("size: {}, capacity: {}\n", v.size(), v.capacity());

	for(auto i{0}; i<10000; ++i) {
		v.push_back(i);
		auto caps = v.capacity();

		if(prev_caps != caps) {
			prev_caps = caps;
			fmt::print("size: {}, capacity: {}\n", v.size(), caps);
		}
	}
}
