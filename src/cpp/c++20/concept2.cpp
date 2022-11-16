#include <concepts>
#include <iostream>
#include <complex>
using namespace std::complex_literals;

template<typename T>
concept Complex = requires(T a, T b) {
    { a.imag() };
    { a.real() };
    { a + b } -> std::convertible_to<T>;
};

template<typename T>
concept Continuous = Complex<T> || std::floating_point<T>;

std::integral auto factorial(std::integral auto a) -> decltype(a) {
    if( a <= 0) return 1;
    else return a * factorial(a - 1);
}

std::floating_point auto factorial(std::floating_point auto a) {
    decltype(a) one = 1.0;
    return std::tgamma(a + one);
}

Complex auto complexGamma(Complex auto a) {
    auto z = 0.0 + 0i;
    return z;
}
int main() {
    std::cout << factorial(10) << std::endl;
    std::cout << factorial(100) << std::endl;
    std::cout << factorial(100UL) << std::endl;
}