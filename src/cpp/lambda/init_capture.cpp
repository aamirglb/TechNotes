#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Baz {
	auto foo() const {
		return [s=s]{ std::cout << s << std::endl; };
	}
	std::string s;
};

int main()
{
	using namespace std::string_literals;
	const std::vector<std::string> vs = {"apple", "orange", "foobar", "lemon"};
	const auto prefix = "foo"s;

	auto result = std::find_if(vs.begin(), vs.end(), [&prefix](const std::string& s) {
				return s == prefix + "bar"s;
			});

	if( result != vs.end())
	{
		std::cout << prefix << " -something found!!\n";
	}

	result = std::find_if(vs.begin(), vs.end(), [savedString = prefix + "bar"s](const std::string& s) {
				return s == savedString;
			});

	if(result != vs.end())
	{
		std::cout << prefix << " - something found!!\n";
	}

	const auto f1 = Baz{"Abc"}.foo();
	const auto f2 = Baz{"xyz"}.foo();
	f1();
	f2();
}
