#include <iostream>

void callWith10(void (*bar)(int), int x)
{
	bar(x);
}

int main()
{
	struct {
		using f_ptr = void(*)(int);

		void operator()(int s) const { return call(s); }
		operator f_ptr() const { return &call; }
	private:
		static void call(int s) { std::cout << s << '\n'; };
	} baz;

	callWith10(baz, 5);
	callWith10([](int x){ std::cout << x << '\n'; }, 15);
}

