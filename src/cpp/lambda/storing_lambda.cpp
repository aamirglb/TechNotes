#include <algorithm>
#include <cctype>
#include <functional>
#include <iostream>
#include <iterator>
#include <vector>

int main()
{
	std::vector<std::function<std::string(const std::string&)>> vecFilters;

	size_t removedSpaceCnt{};
	const auto removeSpaces = [&removedSpaceCnt](const std::string& s) {
		std::string tmp;
		std::copy_if(s.begin(), s.end(), std::back_inserter(tmp), [](char c){ return !std::isspace(c); });
		removedSpaceCnt += s.length() - tmp.length();
		return tmp;
	};

	const auto makeUpperCase = [](const std::string& s) {
		std::string tmp = s;
		std::transform(tmp.begin(), tmp.end(), tmp.begin(), [](unsigned char c){ return std::toupper(c);});
		return tmp;
	};

	vecFilters.emplace_back(removeSpaces);
	vecFilters.emplace_back([](const std::string& x) { return x + " Amazing"; });
	vecFilters.emplace_back([](const std::string& x) { return x + " Modern"; });
	vecFilters.emplace_back([](const std::string& x) { return x + " c++"; });
	vecFilters.emplace_back([](const std::string& x) { return x + " world!"; });
	vecFilters.emplace_back(makeUpperCase);

	const std::string str = "    Hello    ";
	auto temp = str;
	for(const auto& entry : vecFilters)
	{
		temp = entry(temp);
	}
	std::cout << temp;
	std::cout << " \n removed spaces: " << removedSpaceCnt << '\n';
}
