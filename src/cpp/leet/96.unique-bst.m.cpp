// Given an integer n, return the number of structurally unique BST's (binary search trees) which has exactly n nodes of unique values from 1 to n.
#include <vector>
#include <iostream>
using namespace std;

int catalan_number(int n) {
    vector<int> dp(n+1);
    dp[0] = dp[1] = 1;

    for(size_t i = 2; i <= n; ++i) {
        dp[i] = 0;
        for(size_t j = 0; j < i; ++j) {
            dp[i] += dp[j] * dp[i - j - 1];
        }
    }
    return dp[n];
}

int numTrees(int n) {
    return catalan_number(n);
}

int main() {
    cout << numTrees(3) << endl;
    cout << numTrees(1) << endl;
    cout << numTrees(8) << endl;
}