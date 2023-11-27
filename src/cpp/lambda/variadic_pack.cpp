#include <iostream>
#include <tuple>

template <class... Args>
void captureTest(Args... args)
{
	const auto lambda = [args...] {
		const auto tup = std::make_tuple(args...);
		std::cout << "tuple size: " << std::tuple_size<decltype(tup)>::value << '\n';
		/* for(const auto t : tup) { std::cout << t << ", "; } */
		/* template for ( auto elem : tup) std::cout << elem << ", "; */
		std::apply([](auto&&... args){ ((std::cout << args << ", "), ...);}, tup);
		std::cout << std::endl;
	};
	lambda();
}

int main()
{
	captureTest(1, 2, 3, 4, 5);
	captureTest("hello", "world!!", 10.f, 3.14);

	const auto baz = [](int x) noexcept {
		if( x < 20) return x * 1.1;
		else return x * 2.1;
	};
	static_assert(std::is_same_v<double, decltype(baz(10))>, "has to be the same!!");
}
