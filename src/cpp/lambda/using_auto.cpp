#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <type_traits>

int main()
{
	const std::map<std::string, int> numbers {
		{"zero", 0}, {"one", 1}, {"two", 2}, {"three", 3}
	};

	// printing addresses
	for(auto it = numbers.cbegin(); it != numbers.cend(); ++it)
	{
		std::cout << &it->first << ", " << &it->second << '\n';
	}

	std::for_each(std::begin(numbers), std::end(numbers), [](const std::pair<std::string, int>& entry) {
			std::cout << &entry.first << ", " << &entry.second << ": " << entry.first << " = " << entry.second << std::endl;
			});

	// entries are not copied
	std::for_each(std::begin(numbers), std::end(numbers), [](const auto& entry) {
			std::cout << &entry.first << ", " << &entry.second << ": " << entry.first << " = " << entry.second << std::endl;
			});
}
