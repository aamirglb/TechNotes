#include <iostream>
#include <filesystem>
#include <fstream>

int main()
{
    std::ofstream("tmp.txt") << "This is a temporary file!!\n";
    // for(auto& p : std::filesystem::directory_iterator(".")) {
    //     std::cout << p << std::endl;
    // }
}