// g++ -Wall -std=c++17 -I ./include -DFMT_HEADER_ONLY fmt_example.cpp
#include <fmt/format.h>
 
using namespace fmt::literals; // only needed if you are going to use the _a or _format literals.
 
int main()
{
    const int x = 67;
    
    const int y = 45;
 
    const float f = 32.6;
 
    fmt::print("Hello World! This is the number {}\n", x);
 
    fmt::print("This is padded with zeros {:04d} and this is not padded {}\n", x, y);
 
    fmt::print("Floating point formatting with {1} decimal places {0:0.3f}\n", f, 3);
 
    fmt::print(stderr, "{:>25}\n", "Right-aligned");  // printed to the standard error stream
 
    fmt::print("{:>25}\n", "Also right-aligned");
 
    fmt::print("{:^25}\n", "Centered");
 
    // using the _format literal
    std::string message = "This is a {0} string that was {0} with {1}.\n"_format("formatted", "literals");
 
    fmt::print(message);
    
    auto first_name = "Nathaniel";
 
    auto last_name = "Stickley";
    
    auto domain_name = "caltech.edu";
 
    // using the _a literal to name the parameters.
    fmt::print("My name is {first} {last} ({last}@{domain}).\n", 
               "first"_a=first_name, 
               "last"_a=last_name,
               "domain"_a=domain_name);
    
    // print color (this is an experimental feature)
    
//fmt::print_colored(fmt::RED, "Error: "); // this prints to the terminal in red.
    fmt::print("an error message\n");
 
    return 0;
}

