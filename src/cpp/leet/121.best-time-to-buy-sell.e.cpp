#include <iostream>
#include <vector>
using namespace std;

int maxProfit(vector<int>& prices) {
    size_t left {0};
    size_t right {1};
    int maxP = 0;

    while(right < prices.size()) {
        if(prices[left] < prices[right]) {
            auto profit = prices[right] - prices[left];
            maxP = max(profit, maxP);
        } else {
            left = right;
        }
        ++right;
    }
    return maxP;
}

int main() {
    vector<vector<int>> inputs {
        {7, 1, 5, 3, 6, 4},
        {7, 6, 4, 3, 1},
    };

    for(auto& input : inputs) {
        cout << maxProfit(input) << endl;
    }
}