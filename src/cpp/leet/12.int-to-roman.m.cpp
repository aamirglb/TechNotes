// Given an integer, convert it to a roman numeral.

#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

string intToRoman(int num) {
    vector<pair<int32_t, const char*>> roman {
        {1000, "M"},   {900, "CM"},
        {500,  "D"},   {400, "CD"},
        {100,  "C"},   {90,  "XC"},
        {50,   "L"},   {40,  "XL"},
        {10,   "X"},   {9,   "IX"},
        {5,    "V"},   {4,   "IV"},
        {1,    "I"}
    };

    string res{};
    for(const auto& [k, v] : roman) {
        while(num >= k) {
            res += v;
            num -= k;
        }
    }
    return res;
}

int main()
{
    vector<int32_t> v {
        3,
        58,
        1994,
        48
    };

    for(const auto& e : v) {
        cout << e << " -- " << intToRoman(e) << endl;
    }
}