// Given an array of integers nums, find the next permutation of nums.
// The replacement must be in place and use only constant extra memory.

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

void nextPermutation(vector<int>& nums) {
    if(nums.size() == 1) return;

    if(nums.size() == 2) {
        swap(nums[0], nums[1]);
        return;
    }

    if(is_sorted(nums.begin(), nums.end(), greater<int>())) {
        sort(nums.begin(), nums.end());
    } else {
        int x = -1;

        for(size_t i = 0; i < nums.size() - 1; ++i) {
            if(nums[i] < nums[i+1])
                x = i;
        }

        int y = -1;
        for(size_t j = 0; j < nums.size(); ++j) {
            if(nums[x] < nums[j])
                y = j;
        }

        swap(nums[x], nums[y]);
        reverse(nums.begin()+x+1, nums.end());
    }
}

int main()
{
    cout << "\nTC-1\n";
    vector<int> nums {3, 2, 1};
    nextPermutation(nums);
    for(const auto& e: nums) cout << e << ' ';
    cout << endl;

    cout << "\nTC-2\n";
    vector<int> v {1, 1, 5};
    nextPermutation(v);
    for(const auto& e: v) cout << e << ' ';
    cout << endl;

    // vector<int> nums {1, 3, 2};
    // for(const auto& e: nums) cout << e << ' ';
    // cout << endl;
    // nextPermutation(nums);
    // cout << endl;

    // vector<int> v {3, 2, 1};
    // for(const auto& e: v) cout << e << ' ';
    // cout << endl;
    // nextPermutation(v);
    // for(const auto& e: nums) cout << e << ' ';
    // cout << endl;
}