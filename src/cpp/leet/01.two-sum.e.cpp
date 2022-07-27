// Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
// You may assume that each input would have exactly one solution, and you may not use the same element twice.
// You can return the answer in any order.

#include <vector>
#include <map>

using namespace std;

vector<int> twoSum(vector<int> &nums, int target)
{
    map<int, int> m;

    for (int i = 0; i < nums.size(); ++i) {
        auto diff = target - nums[i];
        if (m.count(diff) > 0) {
            return {i, m[diff]};
        } else {
            m[nums[i]] = i;
        }
    }
    return {};

    //         Solution - 1
    //         vector<int> result;

    //         for(size_t i = 0; i < nums.size(); ++i) {
    //             for(size_t j = 0; j < nums.size(); ++j) {
    //                 if( i != j ) {
    //                     if((nums[i] + nums[j]) == target) {
    //                         result.push_back(i);
    //                         result.push_back(j);
    //                         return result;
    //                     }
    //                 }
    //             }
    //         }
    //         return result;
}