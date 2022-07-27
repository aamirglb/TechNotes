// Given a roman numeral, convert it to an integer
#include <string>
#include <map>
#include <vector>
#include <iostream>

using namespace std;

int romanToInt_v2(string s) {
    int result {0};
    size_t i {0};

    map<char, int> m = {
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50},
        {'C', 100},
        {'D', 500},
        {'M', 1000}
    };

    for (const auto &c : s) {
        // previous roman character

        if (i > 0) {
            auto pc = s[i-1];
            if(m[pc] < m[c] ) {
                result -= 2 * m[pc];
            }
        }
        result += m[c];
        ++i;
    }
    return result;
}

int romanToInt(string s) {
    map<string, int> m {
        {"M", 1000}, {"CM", 900},
        {"D", 500},  {"CD", 400},
        {"C", 100},  {"XC", 90},
        {"L", 50},   {"XL", 40},
        {"X", 10},   {"IX", 9},
        {"V", 5},    {"IV", 4},
        {"I", 1},
    };

    int result { 0 };
    size_t i;
    for(i = 0; i < s.length() - 1; ++i) {
        string twoDigits = s.substr(i, 2);
        string oneDigit = string(1, s[i]);

        if(m.count(twoDigits) > 0) {
            result += m[twoDigits];
             ++i;
        } else if(m.count(oneDigit) > 0) {
            result += m[oneDigit];
        }
    }
    result += m[string(1, s[i])];
    return result;
}

int main()
{
    vector<string> inputs {
         "III",
          "LVIII",
          "MCMXCIV",
    };

    for(const auto& s : inputs) {
        cout << s << " -- " << romanToInt_v2(s) << endl;
    }
}