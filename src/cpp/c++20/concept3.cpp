#include <concepts>
#include <iostream>

void print(std::integral auto i) {
    std::cout << "Integral: " << i << '\n';
}

void print(auto x) {
    std::cout << "Non-integral: " << x << '\n';
}

int main() {
    int a = 11;
    long long int b = 22;
    print(a);
    print(b);
}