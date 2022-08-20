// Given an integer array nums sorted in non-decreasing order, remove some duplicates in-place such that each unique element appears at most twice. The relative order of the elements should be kept the same.
#include <iostream>
#include <vector>
#include <fmt/format.h>
#include <fmt/ranges.h>
using namespace std;

void shiftLeft(vector<int>& v, int i, int j) {
    while(j < v.size()) {
        v[i++] = v[j++];
    }
}

int removeDuplicates_v2(vector<int>& nums) {
    int i {};
    int j {1};
    int end = nums.size();

    if(nums.size() < 3) return nums.size();

    while(j < end) {
        while(nums[i] == nums[j]) ++j;
        auto diff = j - i;
        if(j == nums.size()) --j;
        if(diff > 2) {
            end -= (j - (i+2));
            shiftLeft(nums, i+2, j);
            fmt::print("i, j, (j-i), end = {}, {}, {}, {}\n", i, j, diff, end);
            i+=2;
        } else {
            i += diff;
            j += 1;
        }
    }
    fmt::print("{}\n", nums);
    return end;
}

int removeDuplicates(vector<int>& nums) {
    int low {};
    int high {1};
    int cnt {1};

    while(high < nums.size()) {
        if(cnt == 2 && nums[low] == nums[high]) {
            ++high;
            continue;
        }

        if(cnt == 2 || nums[low] != nums[high]) cnt = 0;

        // nums[low] == nums[high] and cnt < 2
        nums[++low] = nums[high];
        ++high;
        ++cnt;

        fmt::print("{}\n", nums);
    }
    return low+1;
}
int main() {
    vector<vector<int>> inputs {
        // {1, 1, 1, 2, 2, 3},
        {0, 0, 1, 1, 1, 1, 2, 3, 3},
        // {0, 0, 0, 0, 1, 1, 1, 1, 2, 3, 3, 4, 4, 4, 5},
        // {1},
        // {1, 1},
        // {1, 1, 1},
    };

    for(auto& input : inputs) {
        fmt::print("in: {}\n", input);
        fmt::print("ou: {}\n", removeDuplicates(input));
        fmt::print("\n\n");
    }
}

