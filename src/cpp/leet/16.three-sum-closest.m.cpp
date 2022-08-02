// Given an integer array nums of length n and an integer target, find three integers in nums such that the sum is closest to target.

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

int threeSumClosest(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    int bestSum {100000};

    for(size_t i = 0; i < nums.size()-2; ++i) {
        auto a = nums[i];
        auto left = i + 1;
        auto right = nums.size() - 1;

        // take two pointers and compute the 3 sum
        while(left < right) {
            // cout << a << " " << nums[left] << " " << nums[right] << endl;
            auto threeSum = a + nums[left] + nums[right];

            if(threeSum == target) return threeSum;
            else if(abs(target - threeSum) < abs(target - bestSum))
                bestSum = threeSum;

            // if 3 sum is bigger, decrease the sum
            if(threeSum > target) {
                --right;
            } else if(threeSum < target) {
                ++left;
            }
        }
    }
    return bestSum;
}

int main()
{
    // vector<int> v {-1, 2, 1, -4};
    // cout << threeSumClosest(v, 1) << endl;

    // vector<int> v2{0, 0, 0};
    // cout << threeSumClosest(v2, 1) << endl;

    // vector<int> v3{1, 1, 1, 0};
    // cout << threeSumClosest(v3, -100) << endl;

    vector<int> v4{4,0,5,-5,3,3,0,-4,-5};
    cout << threeSumClosest(v4, -2) << endl;
}