#include <fmt/format.h>
#include <string>
#include <utility>

using namespace std;

void helper(std::string&& msg) { 
	fmt::print("helper with rvalue reference: {}\n", msg);
}

void handleMessage(string& msg) {
	fmt::print("handleMessage with lvalue reference: {}\n", msg);
}

void handleMessage(string&& msg) {
	// helper(msg); // Error
	helper(std::move(msg));
	//fmt::print("handleMessage with rvalue reference: {}\n", msg);
}


int main() {
	string as { "Hello "};
	handleMessage(as);

	string bs { "World" };
	handleMessage(as+bs);

	handleMessage("Hello, World!!");

	int a {11}, b{22};
	fmt::print("Before exchange a={}, b={}\n", a, b);
	int ret { exchange(a, b) };
	fmt::print("After exchange: a={}, b={}, ret={}\n", a, b, ret);	
}
