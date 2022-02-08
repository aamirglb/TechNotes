#include <fmt/format.h>

class Foo {
public:
	Foo() = default;
	Foo(int a, int b) : m_a{a}, m_b{b}{}
	friend void printFoo(const Foo&);

private:
	int32_t m_a;
	int32_t m_b;
};

void printFoo(const Foo& f) {
	fmt::print("a: {}\nb: {}\n", f.m_a, f.m_b);
	fmt::print("\n");
}

int main() {
	Foo f1;
	printFoo(f1);

	Foo f2 {2, 4};
	printFoo(f2);
}
