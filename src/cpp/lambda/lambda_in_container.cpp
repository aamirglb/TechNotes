#include <iostream>
#include <vector>

int main()
{
	using TFunc = void(*)(int&);
	std::vector<TFunc> v;
	
	v.emplace_back([](int& x) { std::cout << x << '\n'; });
	v.emplace_back([](int& x){ x *= 2; });
	v.emplace_back(v[0]);

	int x = 10;
	for(const auto& entry : v)
	{
		entry(x);
	}

}
