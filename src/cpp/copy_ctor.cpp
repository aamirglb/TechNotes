#include <fmt/format.h>

struct Bar {
	Bar() = delete;
	Bar(const Bar& b) = delete;
	void show() { fmt::print("{}\n", m_value); }
	int32_t m_value{};
};

struct BarTest {
	BarTest() = default;
	BarTest(const BarTest& bt) {}
	Bar b;
};

class Foo {
public:
	Foo() = default;
	Foo(int value) { m_value = value; fmt::print("Foo(int value) called!!\n"); }
	Foo(const Foo& src) { m_value = src.m_value; fmt::print("Foo(const Foo& src) called!!\n"); }
	int32_t m_value;
};

int main() {
	Foo f1;
	Foo f2{ 42 };
	Foo f3{ f2 };

	BarTest bt;

}
