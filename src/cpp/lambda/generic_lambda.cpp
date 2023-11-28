#include <iostream>

template<typename T>
auto sum(T x) { return x; }

template<typename T1, typename... Ts>
auto sum(T1 s, Ts...ts) { return s + sum(ts...); }

int main()
{
	const auto sumLambda = [](auto ...args) {
		std::cout << "sum of: " << sizeof ...(args) << " numbers: ";
		return sum(args...);
	};

	std::cout << sumLambda(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7);
	std::cout << sumLambda(1, 2, 3, 4, 5, 6, 7);
}
