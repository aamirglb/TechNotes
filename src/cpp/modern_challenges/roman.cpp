#include <iostream>
#include <string>
#include <vector>

std::string to_roman(uint32_t value)
{
    std::vector<std::pair<uint32_t, std::string>> roman {
        {1000, "M"},
        {900, "CM"},
        {500, "D"},
        {400, "CD"},
        {100, "C"},
        {90, "XC"},
        {50, "L"},
        {40, "XL"},
        {10, "X"},
        {9, "IX"},
        {5, "V"},
        {4, "IV"},
        {1, "I"},
    };

    std::string result;
    for(auto const & kvp : roman) {
        while(value >= kvp.first) {
            result += kvp.second;
            value -= kvp.first;
        }
    }
    return result;
}

int main()
{
    for(int i = 0; i <= 100; ++i) {
        std::cout << i << "\t" << to_roman(i) << std::endl;
    }

    int number = 0;
    std::cout << "Enter a number: ";
    std::cin >> number;
    std::cout << to_roman(number) << std::endl;
}