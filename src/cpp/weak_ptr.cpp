#include <fmt/format.h>
#include <memory>

using namespace std;

//struct Simple {
//	Simple() { m_ptr = new int{}; }
//	~Simple() { delete m_ptr; }
//	void setValue(int value) { *m_ptr = value; }
//	int32_t *m_ptr;
//};

struct Foo : public enable_shared_from_this<Foo> {
	shared_ptr<Foo> getPointer() {
		return shared_from_this();
	}

	void show() const { fmt::print("Foo::show() called!!\n"); }
};


struct Simple {
	Simple() { fmt::print("Simple constructor called!!\n"); }
	~Simple() { fmt::print("Simple destructor called!!\n"); }
};

unique_ptr<Simple> create() {
	auto ptr { make_unique<Simple>() };
	return ptr;
}

void useResource(weak_ptr<Simple>& wp) {
	auto resource { wp.lock() };
	if(resource) fmt::print("Resource still alive.\n");
	else fmt::print("Resource has been freed!!\n");
}

int main() {
	auto sp { make_shared<Simple>() };
	weak_ptr<Simple> wp { sp };

	useResource(wp);
	sp.reset();
	useResource(wp);

	unique_ptr<Simple> up { create() };
	auto up2 { create() };

	auto p1 { make_shared<Foo>() };
	auto p2 { p1->getPointer() };
	p2->show();
}
