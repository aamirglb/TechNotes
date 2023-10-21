#include <iostream>
#include <map>

namespace
{
    const char* const STRING{"This is a string"};
    char* EDIT_STRING{ "Attemp to Edit" };
}

int main()
{
    // std::cout << STRING << std::endl;
    // std::cout << EDIT_STRING << std::endl;
    // EDIT_STRING[0] = 'a';
    // std::cout << EDIT_STRING << std::endl;
    std::multimap<int, std::string> mm;
    using namespace std::string_literals;
    mm.insert({0, "Hello"s});
    mm.insert({0, "World"s});
    mm.insert({1, "C++"s});
    mm.insert({2, "C"s});
    mm.insert({0, "Rust"s});

    if(auto [first, last] = mm.equal_range(0); first != mm.end())
    {
        while(first != last)
        {
            std::cout << "found element!! ";
            std::cout << first->second << std::endl;
            ++first;
        }
    }
}


