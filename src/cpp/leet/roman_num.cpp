#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <map>

using namespace std;

int romanToDecimal(string &str) {

    map<string, int> m {
        {"M", 1000},
        {"CM", 900},
        {"D", 500},
        {"CD", 400},
        {"C", 100},
        {"XC", 90},
        {"L", 50},
        {"XL", 40},
        {"X", 10},
        {"IX", 9},
        {"V", 5},
        {"IV", 4},
        {"I", 1},
    };

    int result = 0;
    size_t i;
    for(i = 0; i < str.size()-1; ++i) {
        // get two chars

        string s = string(1, str[i]) + string(1, str[i+1]);
        string s1 = string(1, str[i]);

        if(m.count(s) > 0) {
            result += m[s];
            ++i;
        } else {
            if(m.count(s1) > 0) {
                result += m[s1];
            }
        }
    }
    result += m[string(1, str[i])];
    return result;
}

int main()
{
    string s = "XLIX";
    std::cout << romanToDecimal(s) << std::endl;
}