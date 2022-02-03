#include <fmt/format.h>

int main() {
	const char* str1 { R"(Hello "World"!)" };
	const char* str2 { R"(Line-1
Line-2)" };
	const char* str3 { R"-(Embedded )" characters)-" };

	fmt::print("str1: {}\nstr2: {}\nstr3: {}\n", str1, str2, str3);
}
