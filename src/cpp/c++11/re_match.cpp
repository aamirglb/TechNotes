#include <iostream>
#include <regex>
#include <string>
#include <format>

int main()
{
	// regex to match a date in yyyy/mm/dd format
	/*std::regex pattern{ R"re(\d{4}/(?:0?[1-9]|1[0-2])/(?:0?[1-9]|[1-2][0-9]|3[0-1]))re" };*/
	std::regex pattern{ R"re((\d{4})/(0?[1-9]|1[0-2])/(0?[1-9]|[1-2][0-9]|3[0-1]))re" };

	while(true) {
		std::cout << "Enter a date (YYYY/MM/DD) (q=quit): ";
		std::string input;
		if(!getline(std::cin, input) || input == "q") break;

		/*if(std::regex_match(input, pattern)) {*/
		if(std::smatch m; std::regex_match(input, m, pattern)) {
			int year{ std::stoi(m[1])};
			int month{std::stoi(m[2])};
			int day{ std::stoi(m[3])};
			std::cout << std::format(" Valid date: Year={}, month={}, day={}\n", year, month, day);
		} else {
			std::cout << "Invalid date!!" << std::endl;
		}
	}
}
