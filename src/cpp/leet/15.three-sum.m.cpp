// Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.
// Notice that the solution set must not contain duplicate triplets.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> threeSum(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    for(const auto & e : nums) cout << e << ' ';
    cout << endl;
    vector<vector<int>> result;

    for(size_t i = 0; i < nums.size(); ++i) {
        auto a = nums[i];
        // If adjacent elements are same, skip them
        if(i > 0 && a == nums[i - 1]) continue;

        auto left = i + 1;
        auto right = nums.size() - 1;

        // take two pointers and compute the 3 sum
        while(left < right) {
            cout << a << " " << nums[left] << " " << nums[right] << endl;
            auto threeSum = a + nums[left] + nums[right];

            // if 3 sum is bigger, decrease the sum
            if(threeSum > 0) {
                --right;
            } else if(threeSum < 0) {
                ++left;
            } else {
                cout << "[" << a << ", " << nums[left] << ", " << nums[right] << "]" << endl;
                vector<int> v({a, nums[left], nums[right]});
                result.push_back(v);
                ++left;
                while( (nums[left] == nums[left - 1]) && (left < right))
                    ++left;
            }
        }
    }
    return result;
}

int main()
{
    // vector<int> v {-1, 0, 1, 2, -1, -4};
    vector<int> v2 {1, -1, -1, 0};
    threeSum(v2);
}