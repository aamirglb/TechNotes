#include <iterator>
#include <iostream>
#include <string>
#include <algorithm>

int main()
{
	std::istream_iterator<std::string> cinPos{std::cin};
	std::ostream_iterator<std::string> coutPos{std::cout, " "};

	while(cinPos != std::istream_iterator<std::string>()) {
		advance(cinPos, 2);

		if(cinPos != std::istream_iterator<std::string>()) {
			*coutPos++ = *cinPos++;
		} else {
			std::cerr << "cinPos invalid\n";
		}
	}
	std::cout << std::endl;
}

