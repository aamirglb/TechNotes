// #include <boost/random/mersenne_twister.hpp>
#include <boost/random/random_device.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <iostream>

int main() {
    int guess;
    std::cout << "Select number (0-10): ";
    std::cin >> guess;

    if(guess < 0 || guess > 10) {
        return 1;
    }

    // boost::random::mt19937 rng;
    boost::random::random_device rng;
    boost::random::uniform_int_distribution<> ten(0, 10);
    int r = ten(rng);

    if(guess == r) {
        std::cout << "Win\n";
    } else {
        std::cout << "Loss. " << r << "\n";
    }
}