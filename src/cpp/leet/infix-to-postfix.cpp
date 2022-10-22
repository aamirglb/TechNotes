// Convert an infix expression into postfix

#include <iostream>
#include <string>
#include <stack>
#include <map>
#include <vector>

// For left to right assosiative operator, prcedence increase from out to in
// For right to left assosiative operator (like ^), prcedence decrease from out to in

// Outside stack precedence
std::map<char, int> precedenceOutStack {
    {'(', 7}, {')', 0},
    {'*', 3}, {'/', 3},
    {'+', 1}, {'-', 1},
    {'^', 6},
};

// Inside stack precedence
std::map<char, int> precedenceInStack {
    {'(', 0}, /*{')', 3},*/
    {'*', 4}, {'/', 4},
    {'+', 2}, {'-', 2},
    {'^', 5},
};

int getOutPrecedence(char c) {
    if(precedenceOutStack.count(c) > 0) {
        return precedenceOutStack[c];
    } else {
        return 0;
    }
}

int getInPrecedence(char c) {
    if(precedenceInStack.count(c) > 0) {
        return precedenceInStack[c];
    } else {
        return 0;
    }
}

std::string infixToPostfix(std::string infix) {
    std::string postfix {};
    std::stack<char> stk;

    size_t i {};
    // loop through the input string
    while(infix[i]) {
        // if its an operand add it to postfix
        if(std::isalpha(infix[i])) {
            postfix.push_back(infix[i++]);
        } else {
            if(!stk.empty()) {
                auto outPrec = getOutPrecedence(infix[i]);
                auto inPrec = getInPrecedence(stk.top());

                // check the out precedence of input char with in precedence of stack top
                // if its greater push the operator to stack
                if( outPrec > inPrec ) {
                    stk.push(infix[i++]);
                }
                // remove the operator from top of stack
                else if(outPrec < inPrec ) {
                    postfix.push_back(stk.top());
                    stk.pop();
                }
                // only '(' and ')' has equal out and in precedence, ignore them
                else if(outPrec == inPrec) {
                    stk.pop();
                    ++i;
                }
            } else {
                stk.push(infix[i++]);
            }
        }
    }

    // pop out remaining opreator from the stack and append them to postfix
    while(!stk.empty()) {
        postfix.push_back(stk.top());
        stk.pop();
    }
    return postfix;
}

int main()
{
    std::vector<std::string> inputs {
        "a+b*c",          // abc*+
        "A+B*C+D",        // ABC*+D+
        "(A+B)*(C+D)",    // AB+CD+*
        "A*B+C*D",        // AB*CD*+
        "A+B+C+D",        // AB+C+D+
        "((a+b)*c)-d^e^f", // ab+c*def^^-
        "A+B*(C+D)/F+D*E",
        "(a-b/c)*(a/k-l)"  // abc/-ak/l-*

    };
    // std::string infix {"a+b*c-d/e"};

    for(const auto& s : inputs) {
        std::cout << "Infix: " << s << " -- ";
        std::cout << infixToPostfix(s) << std::endl;
    }
}