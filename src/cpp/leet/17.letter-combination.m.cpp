// Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent. Return the answer in any order.

#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

map<string, string> m {
    {'2', "abc"},
    {'3', "def"},
    {'4', "ghi"},
    {'5', "jkl"},
    {'6', "mno"},
    {'7', "pqrs"},
    {'8', "tuv"},
    {'9', "wxyz"},
};



void backtrack(int idx, string curStr, string digits, vector<string> &res) {
    // cout << "curStr: " << curStr << endl;
    if(curStr.length() == digits.length()) {
        res.push_back(curStr);
        return;
    }

    for(const auto& c : m[ digits[idx] ]) {
        // cout << c << ' ';
        backtrack(idx+1, curStr+c, digits, res);
    }
    return;
}
vector<string> letterCombinations(string digits) {
    if(digits.empty()) return {};

    vector<string> result;
    backtrack(0, "", digits, result);
    return result;
}

int main()
{
    cout << "TC-1: digits = 23\n";
    auto result = letterCombinations("23");
    for(const auto &s : result) cout << s << endl;

    cout << "TC-2: digits = ""\n";
    result = letterCombinations("");
    for(const auto &s : result) cout << s << endl;

    cout << "TC-3: digits = 2\n";
    result = letterCombinations("2");
    for(const auto &s : result) cout << s << endl;

    cout << "TC-4: digits = 999\n";
    result = letterCombinations("999");
    for(const auto &s : result) cout << s << endl;
}