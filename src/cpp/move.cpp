#include <fmt/format.h>
#include <utility>
#include <vector>

using namespace std;


class Foo {
public:
	Foo()
		: m_a{}
		, m_b{}
	{ fmt::print("Zero-arg constructor\n"); }

	Foo(int32_t a, int32_t b)
		: m_a{a}
		, m_b{b}
	{ 
		fmt::print("Normal constructor\n"); 
	}

	Foo(const Foo& src)
		: m_a{src.m_a}
		, m_b{src.m_b}
	{ fmt::print("Copy constructor\n"); }

	Foo(Foo&& src) {
		m_a = std::exchange(src.m_a, -1);
		m_b = std::exchange(src.m_b, -1);
		fmt::print("Move constructor\n");
	}

	Foo& operator=(const Foo& rhs) {
		if(this == &rhs) return *this;

		m_a = rhs.m_a;
		m_b = rhs.m_b;
		fmt::print("Copy Assignment operator.\n");
		return *this;
	}

	Foo& operator=(Foo&& rhs) noexcept {
		if(this == &rhs) return *this;
		m_a = exchange(rhs.m_a, -1);
		m_b = exchange(rhs.m_b, -1);
		fmt::print("Move Assignment operator.\n");
		return *this;
	}

	int32_t m_a;
	int32_t m_b;
};

Foo createObject() {
	return Foo {3, 6};
}

class DataHolder {
	public:
		void setData(Foo data) {
			m_data = std::move(data);
		}
	private:
		Foo m_data;
};

int main() {
	DataHolder dh;
	Foo f3;
	dh.setData(f3);
	fmt::print("\n\n");

	dh.setData(Foo{4,4});

	return 0;

	vector<Foo> v;
	fmt::print("vector capacity: {}\n", v.capacity());

	Foo f1 {1, 1};
	f1 = createObject();
	fmt::print("\n");

	Foo f2 {2, 2};
	f2 = f1;

	for(auto i {0}; i < 5; ++i) {
		fmt::print("Iteration - {}\n", i);
		v.push_back(Foo{ 5, 4});
		fmt::print("\n");
		fmt::print("vector capacity: {}\n\n", v.capacity());
	}

	fmt::print("\n\n\n");
}

