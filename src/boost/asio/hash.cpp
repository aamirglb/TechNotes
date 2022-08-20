#include <iostream>
#include <string>
#include <functional>

int main() {
    std::string text {};
    std::cout << "Enter text: ";
    std::cin >> text;

    std::hash<std::string> hashFunc;
    size_t hashText = hashFunc(text);
    std::cout << "Hashed text: " << hashText << std::endl;
}