#include <fmt/format.h>
#include <initializer_list>

struct Foo {
	Foo(int) { fmt::print("{}(int) called.\n", __func__); }
	Foo(int, int) { fmt::print("{}(int, int) called.\n", __func__); }
};

struct Bar {
	explicit Bar(int) { fmt::print("{}(int) called.\n", __func__); }
	explicit Bar(int, int) { fmt::print("{}(int, int) called.\n", __func__); }
};

void process(const Foo& c) {}
void process2(const Bar& c) {}

int main() {
	process(1);
	process({1});
	process({1, 2});

	// process2(1);
	process2(Bar{1});
	process2(Bar{1, 2});
}
