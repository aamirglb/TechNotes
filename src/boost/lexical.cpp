#include <boost/lexical_cast.hpp>
#include <string>
#include <iostream>

int main() {
    try {
        std::string s1;
        std::cout << "Enter num1: ";
        std::cin >> s1;

        int n1 = boost::lexical_cast<int>(s1);
        std::cout << "Enter num2: ";
        std::cin >> s1;
        int n2 = boost::lexical_cast<int>(s1);
        std::cout << "sum = " << n1 + n2 << std::endl;
    } catch(const boost::bad_lexical_cast &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}