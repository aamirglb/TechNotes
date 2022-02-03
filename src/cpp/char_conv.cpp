#include <charconv>
#include <string>
#include <fmt/format.h>

using namespace std;

int main() {
	const size_t BufferSize { 50 };
	string out(BufferSize, ' ');
	auto result { to_chars(out.data(), out.data()+out.size(), 12345) };
	if(result.ec == errc{}) {
		fmt::print("{}\n", out);
	}

	double value { 0.314 };
	string out2(BufferSize, ' ');
	auto [ptr, error] { to_chars(out.data(), out.data()+out.size(), value) };
	if(error == errc{}) {
		fmt::print("{}\n", out2);
	}
}
