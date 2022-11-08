#include <iostream>
#include <random>
#include <vector>
#include <limits>

class Rand_int {
public:
    Rand_int(int low, int high)
    : dist{low, high}
    {}

    int operator()() { return dist(re); }  // draw an int
    void seed(int s) { re.seed(s); }   // choose new random engine seed
private:
    std::default_random_engine re;
    std::uniform_int_distribution<> dist;
};

int main() {
    constexpr int max {9};
    Rand_int rnd{0, max};
    rnd.seed(300683);

    if(std::numeric_limits<char>::is_signed)
        std::cout << "char is signed.\n";
    else
        std::cout << "char is unsigned\n";

    std::vector<int> histogram(max+1);
    for(int i = 0; i!=200; ++i)
        ++histogram[rnd()];

    for(int i = 0; i != histogram.size(); ++i) {
        std::cout << i << " (" << histogram[i] << ")" << '\t';
        for(int j = 0; j != histogram[i]; ++j) std::cout << '*';
        std::cout << std::endl;
    }
}