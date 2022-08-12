// Given an integer array nums and an integer k, return true if there are two distinct indices
// i and j in the array such that nums[i] == nums[j] and abs(i - j) <= k.

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

bool containsNearbyDuplicate(vector<int>& nums, int k) {
    unordered_map<int, int> m;
    for(int i = 0; i < nums.size(); ++i) {
        auto n = nums[i];

        if(m.count(n) > 0) {
            if(abs(m[n] - i) <= k) return true;
            m[n] = i;
        } else {
            m[n] = i;
        }
    }
    return false;
    // for(int i = 0; i < nums.size() - 1; ++i) {
    //     for(int j = i+1; j < nums.size(); ++j) {
    //         if(nums[i] == nums[j]) {
    //             if(abs(i - j) <= k) return true;
    //         }
    //     }
    // }
    return false;
}

int main() {
    cout << boolalpha << containsNearbyDuplicate({1, 2, 3, 1}, 3) << endl;
    cout << boolalpha << containsNearbyDuplicate({1, 0, 1, 1}, 3) << endl;
}