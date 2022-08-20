// You are given an integer array nums that is sorted in non-decreasing order.
// Determine if it is possible to split nums into one or more subsequences such that both of the following conditions are true:

// 1. Each subsequence is a consecutive increasing sequence (i.e. each integer is exactly one more than the previous integer).
// 2. All subsequences have a length of 3 or more.

#include <iostream>
#include <vector>
#include <unordered_map>
#include <fmt/format.h>
#include <fmt/ranges.h>
using namespace std;

bool isPossible(vector<int>& nums) {
    unordered_map<int, int> ones;
    unordered_map<int, int> twos;
    unordered_map<int, int> threes;

    for(const auto& e : nums) {
        auto n = e - 1;
        if(ones.count(n) > 0 && ones[n] > 0) {
            ones[n]--;
            twos[e]++;
            continue;
        }

        if(twos.count(n) > 0 && twos[n] > 0) {
            twos[n]--;
            threes[e]++;
            continue;
        }

        if(threes.count(n) > 0 && threes[n] > 0) {
            threes[n]--;
            threes[e]++;
            continue;
        }
        ones[e]++;
    }
    int onesTotal{}, twosTotal{};
    for(auto& [_, v] : ones) onesTotal += v;
    for(auto& [_, v] : twos) twosTotal += v;

    if(onesTotal > 0 || twosTotal > 0) return false;
    return true;
}

// bool isPossible(vector<int>& nums) {
//     unordered_map<int, int> m1; // frequency map
//     unordered_map<int, int> m2;

//     for(const auto& e : nums) {
//         m1[e]++;
//     }

//     for(const auto& e : nums) {
//         fmt::print("checking {} - {} ", e, m1[e]);
//         if(m1[e] == 0) { fmt::print("\n"); continue; }

//         if(m2[e] > 0) {
//             m1[e]--;
//             m2[e]--;
//             m2[e+1]++;
//         } else if(m1[e+1] > 0 &&
//                   m1[e+2] > 0) {
//                 m1[e]--;
//                 m1[e+1]--;
//                 m1[e+2]--;
//                 m2[e+3]++;
//         } else {
//             return false;
//         }
//         // m1[e]--;
//         fmt::print(" -- done\n");
//     }
//     return true;
// }

// bool isPossible(vector<int>& nums) {
//         unordered_map<int, int> dict, temp;
//         for (auto& ele: nums) dict[ele]++;
//         for (auto& ele: nums){
//             if (dict[ele]==0)   //if the ele is already used in some sequence
//                 continue;
//             else if (temp[ele]>0){  //if the ele can be added in the last consecutive sequence
//                 dict[ele]--;
//                 temp[ele]--;
//                 temp[ele+1]++;

//             }else if (dict[ele+1]>0 && dict[ele+2]>0){ //this ele should form a consecutive sequence by itself since it cannot be appended to a previous sequence
//                 dict[ele]--;
//                 dict[ele+1]--;
//                 dict[ele+2]--;
//                 temp[ele+3]++;
//             }else //doesn't belong to any consecutive sequence
//                 return false;
//         }
//         return true;
//     }

int main() {
    vector<vector<int>> inputs {
        {1, 2, 3, 3, 4, 5},
    };

    fmt::print("{}\n", isPossible(inputs[0]));
    fmt::print("Done\n");

    // for(const auto& e: inputs[0]) {
    //     if(e == 3) continue;
    //     fmt::print("{} ", e);
    // }

    // unordered_map<char, int> m {
    //     {'a', 3},
    //     {'b', 1},
    //     {'c', 4},
    // };

    // fmt::print("{}\n", m.count('e'));
}