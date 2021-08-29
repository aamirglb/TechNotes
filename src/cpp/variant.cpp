#include <variant>
#include <iostream>

int main() {
    std::variant<int, std::string> var{"hi"};
    std::cout << var.index() << '\n';
    var = 42;
    std::cout << var.index() << '\n';

    try {
        int i = std::get<0>(var);
        std::string s = std::get<std::string>(var);
    } 
    catch(const std::bad_variant_access& e) {
        std::cerr << "EXCEPTION: " << e.what() << '\n';
    }
}