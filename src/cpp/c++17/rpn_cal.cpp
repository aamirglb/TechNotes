#include <iostream>
#include <stack>
#include <iterator>
#include <map>
#include <sstream>
#include <cassert>
#include <vector>
#include <stdexcept>
#include <cmath>

template <typename IT>
double evalute_rpn(IT it, IT end) {
    std::stack<double> stk;

    auto pop_stack([&](){
        auto r{ stk.top() };
        stk.pop();
        return r;
    });

    std::map<std::string, double(*)(double, double)> ops {
        {"+", [](double a, double b) { return a + b; }},
        {"-", [](double a, double b) { return a - b; }},
        {"*", [](double a, double b) { return a * b; }},
        {"/", [](double a, double b) { return a / b; }},
        {"^", [](double a, double b) { return pow(a, b); }},
        {"%", [](double a, double b) { return fmod(a, b); }},
    };

    for(; it != end; ++it) {
        std::stringstream ss {*it};

        if(double val; ss >> val) {
            stk.push(val);
        } else {
            const auto r {pop_stack()};
            const auto l {pop_stack()};

            try {
                const auto& op {ops.at(*it)};
                const double result {op(l, r)};
                stk.push(result);
            } catch(const std::out_of_range& ) {
                throw std::invalid_argument(*it);
            }
        }
    }
    return stk.top();
}

int main() {
    try {
        std::cout << evalute_rpn(std::istream_iterator<std::string>{std::cin}, {}) << std::endl;
    } catch(const std::invalid_argument &e) {
        std::cout << "Invalid operator: " << e.what() << std::endl;
    }
}







