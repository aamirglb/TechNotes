#include <iostream>
#include <string.h>
#include <utility>

void foo(const std::string&) { std::cout << "foo(const string&)\n"; }
void foo(const std::string&&) { std::cout << "foo(const string&&)\n"; }

template<typename T>
void callTemplateFoo(T&& str) {
	std::cout << "Calling foo() on: " << str << '\n';
	foo(std::forward<T>(str));
}

int main()
{
	const auto callFoo = [](auto&& str) {
		std::cout << "calling foo() on: " << str << '\n';
		foo(std::forward<decltype(str)>(str));
	};

	const std::string str = "Hello World";
	callFoo(str);
	callFoo("Hello World Ref Ref");

	callTemplateFoo(str);
	callTemplateFoo("Hello World Ref Ref");
}
