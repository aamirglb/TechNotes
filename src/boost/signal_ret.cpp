#include <boost/signals2.hpp>
#include <iostream>


float print_sum(float x, float y) {
    return x+y;
}

float print_product(float x, float y) {
    return x*y;
}

float print_diff(float x, float y) {
    return x-y;
}

float print_quotient(float x, float y) {
    return x/y;
}

template<typename T>
struct maximum {
    typedef T result_type;

    template<typename InputIterator>
    T operator()(InputIterator first, InputIterator last) const {
        if(first == last) return T();
        T max_value = *first++;
        while(first != last) {
            if(max_value < *first)
                max_value = *first;
            ++first;
        }
        return max_value;
    }
};

int main(int argc, char *argv[]) {
    boost::signals2::signal<float (float, float), maximum<float> > sig;
    // sig.connect(&print_args);
    sig.connect(&print_sum);
    sig.connect(&print_product);
    sig.connect(&print_quotient);
    sig.connect(&print_diff);

    std::cout << sig(5., 3.) << std::endl;
}