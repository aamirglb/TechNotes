// You have n coins and you want to build a staircase with these coins. The staircase consists of k rows where the ith row has exactly i coins. The last row of the staircase may be incomplete.
// Given the integer n, return the number of complete rows of the staircase you will build.

#include <iostream>
#include <fmt/format.h>

int arrangeCoins(int n) {
    int count {};
    int i{1};
    while(n >= i) {
        ++count;
        n -= i;
        ++i;
    }
    return count;
}

int main() {
    fmt::print("{}\n", arrangeCoins(5));
    fmt::print("{}\n", arrangeCoins(8));
    fmt::print("{}\n", arrangeCoins(10));
    fmt::print("{}\n", arrangeCoins(11));
}