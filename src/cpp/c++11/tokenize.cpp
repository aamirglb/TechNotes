#include <iostream>
#include <string>
#include <format>
#include <regex>

int main()
{
	std::regex pattern{ R"re(\s*[,:\{\}]\s*?)re" };
	std::string input{"{11:EOW,12:WGS84,13:45.012057744513221,14:-64,15:1000,16:9.0173440537629048,17:15.960000000000001,2:1733045686222000,200:false,86:45.127630545849939,87:-63.977100659497466,88:45.127631129846222,89:-64.022892692088149}"};

	const std::sregex_token_iterator end;
	for(std::sregex_token_iterator itr{std::cbegin(input), std::cend(input), pattern, -1};
			itr != end; ++itr) {
		std::cout << std::format("{}\n", itr->str());
	}
}
