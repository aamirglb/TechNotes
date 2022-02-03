#include <string>
#include <string_view>
#include <fmt/format.h>

using namespace std;

string_view extractExtension(string_view filename) {
	return filename.substr(filename.rfind('.'));
}

int main() {
	string filename { R"(c:\temp\my file.ext)" };
	fmt::print("c++ string: {}\n", extractExtension(filename));

	const char* cString { R"(c:\temp\my file.ext)" };
	fmt::print("c string: {}\n", extractExtension(cString));

	fmt::print("Literal: {}\n", extractExtension(R"(c:\temp\my file.ext)"));
}

