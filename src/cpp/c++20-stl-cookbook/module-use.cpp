// g++ -Wall -Wextra -pedantic -std=c++20 -fmodules-ts hello-m.cpp module-use.cpp -xc++-system-header iostream
import hello;
import my_math;
import <iostream>;
export import <string>;

// import std.core;

int main()
{
    hello();
    double f = add(4.5, 3.25);
    double i = add(21, 42);
    std::string s = add<std::string>("one ", "two");
    std::cout << f << std::endl;
    std::cout << i << std::endl;
    // std::cout << s << std::endl;
}