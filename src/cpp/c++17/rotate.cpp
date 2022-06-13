#include <iostream>
#include <algorithm>
#include <iterator>
#include <set>

int main()
{
	std::set<int> s;
	for(size_t i = 0; i < 10; ++i) s.insert(s.end(), i);
	std::copy(s.cbegin(), s.cend(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	auto pos = std::next(s.cbegin());
	std::rotate_copy(s.cbegin(),
			pos,
			s.cend(),
			std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	pos = s.cend();
	std::advance(pos, -2);
	std::rotate_copy(s.cbegin(),
			pos,
			s.cend(),
			std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
}

