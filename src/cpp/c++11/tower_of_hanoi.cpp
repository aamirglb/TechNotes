#include <iostream>

using Tower = int32_t;
int32_t num_of_moves{};

void tower_of_hanoi(int32_t n, Tower a, Tower b, Tower c)
{
    if(n > 0)
    {
        ++num_of_moves;
        tower_of_hanoi(n-1, a, c, b);
        std::cout << "(" << a << ", " << c << ")\n";
        tower_of_hanoi(n-1, b, a, c);
    }
}

// quick questions
int f(int &x, int c)
{
    c = c - 1;
    if (c == 0)
        return 1;
    x = x + 1;
    std::cout << x << " " << c << std::endl;
    return f(x, c) * x;
}

int main()
{
    // tower_of_hanoi(4, 1, 2, 3);
    // std::cout << "Number of moves: " << num_of_moves << std::endl;

    int x = 5;
    std::cout << f(x, x) << std::endl;

    for(size_t i = 0; i < 5; ++i) {
        std::cout << "aeiou"[i] << " ";
    }
}