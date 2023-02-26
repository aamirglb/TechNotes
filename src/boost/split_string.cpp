#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<std::string> result;
    std::string input = {
        R"({"name":"Move","user":1,"robot":2,"map":1,"x":"4","y":"87"},{"name":"Wait","user":1,"robot":2,"map":1,"mins":"3"},{"name":"ReturnHome","user":1,"robot":2,"map":1,"RH":"yes"})"};

    std::cout << input << "\n";

    int start{};
    std::size_t found = input.find("},");
    while (found != std::string::npos)
    {
        result.push_back(input.substr(start, found + 1));
        start = found + 2;
        found = input.find("},", start);
    }

    for (const auto &s : result)
    {
        std::cout << s << std::endl;
    }
}