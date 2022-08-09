// Given a non-empty array of integers nums, every element appears twice except for one. Find that single one.
// You must implement a solution with a linear runtime complexity and use only constant extra space.

#include <iostream>
#include <vector>

using namespace std;

int singleNumber(vector<int>& nums) {
    if(nums.size() == 1) return nums[0];
    int ans {};
    for(const auto& e : nums) {
        ans = ans ^ e;
    }
    return ans;
}

int main()
{
    vector<vector<int>> inputs {
        {2, 2, 1},
        {4, 1, 2, 1, 2},
        {1},
    };

    for(auto& input : inputs) {
        cout << singleNumber(input) << endl;
    }
}
