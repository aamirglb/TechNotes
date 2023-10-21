#include <iostream>
#include <regex>

int main()
{
    std::regex pattern("(a|e|i|o|u){2}");
    std::smatch r;
    std::string input{"aamir ai"};
    while (std::regex_search(input, r, pattern))
    {
        std::cout << "match: " << r.str() << std::endl;
        input = r.suffix();
    }
}