// Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.

#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

int longestValidParentheses(string s) {
    stack<char> stk;
    int maxValid = 0;
    int currCnt {};

    for(size_t i = 0; i < s.length(); ++i) {
        if(s[i] == '(') {
            stk.push(s[i]);
        } else {
            if(!stk.empty() && stk.top() == '(') {
                stk.pop();
                currCnt+=2;
                if(currCnt > maxValid)
                    maxValid = currCnt;
            } else {
                if(currCnt > maxValid) {
                    maxValid = currCnt;
                }
                currCnt = 0;
            }
        }
    }
    return maxValid;
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
