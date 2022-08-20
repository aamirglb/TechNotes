// Given two non-negative integers, num1 and num2 represented as string, return the sum of num1 and num2 as a string.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fmt/format.h>
#include <fmt/ranges.h>
using namespace std;

string addStrings(string num1, string num2) {
    int n = num1.length() - 1;
    int m = num2.length() - 1;
    int carry {};
    vector<char> res;

    while(n >= 0 && m >= 0) {
        int d1 = num1[n--] - '0';
        int d2 = num2[m--] - '0';
        int r = d1 + d2 + carry;
        res.push_back(r % 10 + '0');
        carry = r / 10;
    }

    while(n >= 0) {
        int r = num1[n--] - '0' + carry;
        res.push_back(r % 10 + '0');
        carry = r / 10;
    }

    while(m >= 0) {
        int r = num2[m--] - '0' + carry;
        res.push_back(r % 10 + '0');
        carry = r / 10;
    }

    if(carry != 0) res.push_back(carry + '0');
    reverse(res.begin(), res.end());
    return string{res.begin(), res.end()};
}

int main() {
    fmt::print("{}\n", addStrings("11", "123"));
    fmt::print("{}\n", addStrings("456", "77"));
    fmt::print("{}\n", addStrings("0", "0"));
}