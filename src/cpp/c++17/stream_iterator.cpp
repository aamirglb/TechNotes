#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>

int main()
{
	std::vector<int> v;
	for(size_t i = 0; i < 11; ++i) v.push_back(i);

	std::ofstream f("out.txt", std::ios::out);
	if(f.is_open()) {
		std::string delim{", "};
		std::copy(v.cbegin(), v.cend(), std::ostream_iterator<int>(f, delim.c_str()));
		f.close();
	} else {
		std::cerr << "Unable to open file\n";
	}

	std::ifstream i("out.txt", std::ios::in);
	if(i.is_open()) {
		int value;
		std::string delim;
		while(i >> value >> delim) {
			std::cout << "value: " << value << " delim: " << delim << std::endl;
		}
	} else {
		std::cerr << "Unable to open file for reading\n";
	}

	std::ostream_iterator<int> intWriter(std::cout, "\n");
	*intWriter = 42;
	++intWriter;
	*intWriter = 77;
	*intWriter = -5;
}

