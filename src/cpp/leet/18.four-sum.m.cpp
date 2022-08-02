// Given an array nums of n integers, return an array of all the unique quadruplets [nums[a], nums[b], nums[c], nums[d]] such that:
// 0 <= a, b, c, d < n
// a, b, c, and d are distinct.
// nums[a] + nums[b] + nums[c] + nums[d] == target

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

vector<vector<int>> fourSum(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> result;
    size_t sz = nums.size();
    set<vector<int>> st;

    for(size_t i = 0; i < sz - 2; ++i) {
        for(size_t j = i+1; j < sz-2; ++j) {
            vector<int> v {nums[i], nums[j]};
            size_t left = j+1;
            size_t right = sz - 1;
            auto sum = nums[i] + nums[j];

            while(left < right) {
                auto r = sum + nums[left] + nums[right];
                if(r == target) {
                    v.push_back(nums[left]);
                    v.push_back(nums[right]);
                    st.insert(v);
                    v.pop_back();
                    v.pop_back();
                    left++;
                } else if(r > target) {
                    --right;
                } else {
                    ++left;
                }
            }
        }
    }
    for(const auto& e: st) {
        // for(const auto &ee: e) cout << ee << ' '; cout <<endl;
        result.push_back(e);
    }
    return result;
}

// vector<vector<int>> fourSum(vector<int>& nums, int target) {
//     sort(nums.begin(), nums.end());
//     for(const auto &e: nums) cout << e << ' ';
//     cout << " target = " << target << endl;
//     vector<vector<int>> result;
//     // int bestSum {numeric_limits<int>::max()};

//     for(size_t i = 0; i < nums.size()-3; ++i) {
//         auto a = nums[i];
//         for()
//         auto next = i + 1;
//         auto left = i + 2;
//         auto right = nums.size() - 1;

//         // take two pointers and compute the sum
//         while(left < right) {
//             // cout << a << " " << nums[left] << " " << nums[right] << endl;
//             auto fourSum = a + nums[next] + nums[left] + nums[right];

//             if(fourSum == target) {
//                 vector<int> v {nums[i], nums[i+1], nums[left], nums[right]};
//                 cout << "** " << nums[i] << " " << nums[i+1] << " " << nums[left] << " " << nums[right] << endl;
//                 result.push_back(v);
//                 ++left;
//                 // --right;
//                 // ++next;
//                 // left = i + 2;
//                 // right = nums.size() - 1;
//             }
//             else if(fourSum < target) {
//                 ++left;
//             } else {
//                 --right;
//             }
//         }
//     }
//     return result;
// }

int main() {
    vector<int> v {1, 0, -1, 0, -2, 2};
    int target {0};

    auto r = fourSum(v, target);
}