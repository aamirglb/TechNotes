#include <iostream>
#include <typeinfo>

// void test1()
// {
// 	int i = 0;
// 	decltype(i++) j;
// 	std::cout<<"typeid of j: " << typeid(j).name() << std::endl;
// }

// void test2()
// {
// 	int i = 0;
// 	int m = 1;
// 	decltype(++i) k = m;
// 	std::cout << "typeid of k: " << typeid(k).name() << std::endl;
// }

int main()
{
	// test1();
	// test2();

	int32_t a {};
	decltype(a++) b; // OK

	int32_t c{};
	decltype(++c) d = b; // error: 'd' declared as reference but not initialized

	std::cout << "typeid(b) = " << typeid(b).name() << std::endl;
	std::cout << "typeid(d) = " << typeid(d).name() << std::endl;
}

