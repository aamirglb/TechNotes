#include <fmt/format.h>

class Demo {
	public:
		void display() { fmt::print("{}: 5\n", __func__); }
};

void display() { fmt::print("{}: 10\n", __func__); }

namespace NS {
	void display() { fmt::print("{}: 20\n", __func__); }
}

int main() {
	Demo d;
	d.display();
	NS::display();
	::display();
	display();
}
