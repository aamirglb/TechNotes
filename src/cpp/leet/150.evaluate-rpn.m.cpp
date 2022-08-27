// Evaluate the value of an arithmetic expression in Reverse Polish Notation.
// Valid operators are +, -, *, and /. Each operand may be an integer or another expression.

#include <vector>
#include <string>
#include <unordered_map>
#include <stack>
#include <iostream>
using namespace std;

int evalRPN(vector<string>& tokens) {
    stack<int> stk;
    unordered_map<string, char> ops{
        {"+", '+'},
        {"-", '-'},
        {"*", '*'},
        {"/", '/'},
    };

    for (auto &token : tokens)
    {
        if (ops.find(token) != ops.end())
        {

            int b = stk.top();
            stk.pop();
            int a = stk.top();
            stk.pop();
            int ans{};

            switch (ops[token])
            {
            case '+':
                ans = a + b;
                break;
            case '-':
                ans = a - b;
                break;
            case '*':
                ans = a * b;
                break;
            case '/':
                ans = a / b;
                break;
            }
            stk.push(ans);
        }
        else
        { // its an operand
            stk.push(stoi(token));
        }
    }
    return stk.top();
}

int main() {
    vector<vector<string>> inputs {
        {"2","1","+","3","*"},
        {"4","13","5","/","+"},
        {"10","6","9","3","+","-11","*","/","*","17","+","5","+"},
    };
    for(auto& input : inputs) {
        cout << evalRPN(input) << std::endl;
    }
}