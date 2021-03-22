#include <boost/signals2.hpp>
#include <iostream>

void print_args(float x, float y) {
    std::cout << "The arguments are " << x << " and " << y << std::endl;
}

void print_sum(float x, float y) {
    std::cout << "Sum: " << x+y << std::endl;
}

void print_product(float x, float y) {
    std::cout << "Product: " << x*y << std::endl;
}

void print_diff(float x, float y) {
    std::cout << "Diff: " << x-y << std::endl;
}

void print_quotient(float x, float y) {
    std::cout << "Quotient: " << x/y << std::endl;
}

int main(int argc, char *argv[]) {
    boost::signals2::signal<void (float, float)> sig;
    sig.connect(&print_args);
    sig.connect(&print_sum);
    sig.connect(&print_product);
    sig.connect(&print_diff);
    sig.connect(&print_quotient);

    sig(5., 3.);
}