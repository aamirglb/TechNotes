#include<iostream>
#include<random>
int main() {
    std::mt19937 g;
    unsigned seed{ 65472381u };
    g.seed(seed);
    std::cout << "Seed : " << seed << "\n\n";
    for (int i = 0; i < 10; ++i) {
        std::cout << "g() : " << g() << "\n";
    }
}