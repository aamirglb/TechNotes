// Given an integer array nums, move all 0's to the end of it while maintaining the relative order of the non-zero elements.
// Note that you must do this in-place without making a copy of the array.

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void moveZeroes(vector<int>& nums) {
    if(nums.size() == 1) return;

    // count number of zeros
    auto zeros = count_if(nums.begin(), nums.end(), [](int e) {return e==0;});

    for(size_t j = 0; j < zeros; ++j) {
        for(size_t i = 0; i < nums.size() - 1; ++i) {
            if(nums[i] == 0) {
                auto tmp = nums[i+1];
                nums[i+1] = nums[i];
                nums[i] = tmp;
            }
        }
    }

    for(const auto& e: nums) {
        cout << e << ' ';
    } cout << endl;
}

int main() {
    vector<vector<int>> inputs {
        {0, 1, 0, 3, 12},
        // {0},
    };

    for(auto& input : inputs) {
        moveZeroes(input);
    }
}