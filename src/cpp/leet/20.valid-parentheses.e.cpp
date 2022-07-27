// Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

bool isValid(string s) {
    stack<char> stk;

    for(const char& c : s) {
        if(c == '(' || c == '{' || c == '[') {
            stk.push(c);
        } else {
            if(stk.empty()) return false;
            auto top = stk.top();
            switch(c) {
                case ')':
                    if(top != '(') return false;
                break;

                case '}':
                    if(top != '{') return false;
                break;

                case ']':
                    if(top != '[') return false;
                break;
            }
            stk.pop();
        }
    }
    return stk.empty();
}

int main()
{
    vector<string> v {
        "()",
        "()[]{}",
        "(]",
        "([)]{}",
        "]",
    };

    for(const auto &e : v) {
        cout << e << " -- " << boolalpha << isValid(e) << endl;
    }
}