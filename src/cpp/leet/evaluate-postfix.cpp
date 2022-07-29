// Evaluate a posfix expression
#include <iostream>
#include <stack>
#include <string>
#include <vector>

int evaluatePostfix(std::string postfix) {
    std::stack<int> stk;
    size_t i = 0;

    while(postfix[i]) {
        if(std::isdigit(postfix[i])) {
            stk.push(postfix[i++] - '0');
        } else {
            auto op = postfix[i++];
            auto op2 = stk.top(); stk.pop(); // IMP!!
            auto op1 = stk.top(); stk.pop();

            switch(op) {
                case '+':
                    stk.push(op1+op2);
                    break;
                case '-':
                    stk.push(op1 - op2);
                    break;
                case '*':
                    stk.push(op1 * op2);
                    break;
                case '/':
                    stk.push(op1 / op2);
                    break;
            }
        }
    }
    return stk.top();
}

int main()
{
    std::vector<std::string> inputs {
        "35*62/+4-",
        "65+34*+",
        "234*+82/-"
    };

    for(const auto &s: inputs) {
        std::cout << s << " = " << evaluatePostfix(s) << std::endl;
    }
}