#include <iostream>
#include <memory>

struct Simple {
	Simple() { std::cout << ++m_id << " : Simple constructor called!\n"; }
	~Simple() { std::cout << m_id-- << ": Simple destructor called!\n"; }
	int32_t getId() const { return m_id; };
	static int32_t m_id;
};

int32_t Simple::m_id {};

struct Foo {
	Foo() {
		m_counter = 42;
	}

	void show() const { std::cout << m_counter << '\n'; }

	private:
		int32_t m_counter;
};

struct Bar {
	Bar(int32_t b) : m_b {b} {}
	int32_t getB() const { return m_b; }
	void setB(int32_t b) { m_b = b; }
	int32_t m_b;
};

void updateB(std::shared_ptr<Bar> bp) {
	bp->setB(33);
}

int main() {
	int *ptr { new int };
	delete ptr;
	ptr = nullptr;
	delete ptr;

	Foo* f1 { (Foo*)malloc(sizeof(Foo)) };
	Foo* f2 { new Foo{} };

	f1->show();
	f2->show();

	Simple *s { new Simple[4] };
	delete[] s;

	const wchar_t* str { L"Hello, World!!" };
	std::cout << *str << std::endl;

	auto sp { std::make_unique<Simple>() };
	std::cout << sp->getId() << std::endl;

	auto arr { std::make_unique<int[]>(5) };
	for(auto i {0}; i < 5; ++i) std::cout << arr[i] << ", "; 
	std::cout << '\n';

	// C++20 
	//auto arr1 { std::make_unique_for_overwrite<int[]>(5) };
	//for(auto i {0}; i < 5; ++i) std::cout << arr1[i] << ", "; 
	//std::cout << '\n';
	
	auto b { std::make_shared<Bar>(4) };
	std::cout << "b: " << b->getB() << '\n';
	updateB(b);
	std::cout << "b: " << b->getB() << '\n';

}
