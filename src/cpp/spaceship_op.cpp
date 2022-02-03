#include <iostream>
#include <fmt/format.h>
//#include <compare>
#include <string>

int main(int argc, char *argv[]) {
	using namespace std;
	int i {11};
	if(argc > 1)
		i = atoi(argv[1]);
	strong_ordering result { i <=> 0 };
	if(result == strong_ordering::less)
		fmt::print("less\n");
	if(result == strong_ordering::greater)
		fmt::print("greater\n");
	if(result == strong_ordering::equal)
		fmt::print("equal\n");
}
	
