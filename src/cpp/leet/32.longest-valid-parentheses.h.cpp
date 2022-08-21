// Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <fmt/format.h>
#include <fmt/ranges.h>
using namespace std;

int longestValidParentheses(string s) {
    stack<int> stk;
    int maxLen {};
    stk.push(-1);

    for(int i = 0; i < s.length(); ++i) {
        if(s[i] == '(') stk.push(i);
        else {
            stk.pop();
            if(stk.empty()) {
                stk.push(i);
            } else {
                int len = i - stk.top();
                maxLen = std::max(maxLen, len);
            }
        }
    }
    return maxLen;
}

int main() {
    vector<string> inputs {
        "(()",
        ")()()(())",
        "()(()",
    };

    for(const auto& s : inputs) {
        cout << longestValidParentheses(s) << endl;
    }
}
