#include <iostream>
#include <vector>
#include <fmt/format.h>
#include <fmt/ranges.h>
using namespace std;

int findRotationPoint(vector<int>& nums) {
    int i{};
    while((i < (nums.size() - 1)) &&
           nums[i] <= nums[i+1])
        ++i;
    return i+1;
}

bool binarySearch(vector<int>& v, int target, int low, int high) {
    while(low <= high) {
        auto mid = (low+high)/2;
        if(v[mid] == target) return true;
        else if(target < v[mid]) {
            high = mid -1;
        } else {
            low = mid + 1;
        }
    }
    return false;
}
bool search(vector<int>& nums, int target) {
    if(nums.size() == 1) {
        if(nums[0] == target) return true;
        else return false;
    }

    int pivot = findRotationPoint(nums);
    fmt::print("pivot: {}\n", pivot);
    bool res = binarySearch(nums, target, 0, pivot-1);
    if(!res) {
        res = binarySearch(nums, target, pivot, nums.size()-1);
    }
    return res;
}

int main() {
    vector<vector<int>> inputs {
        {2, 5, 6, 0, 0, 1, 2},
        {5, 6},
        {2, 2, 2, 3, 2, 2, 2},
        {1, 1}
    };

    // fmt::print("{}\n", search(inputs[0], 0));
    // fmt::print("{}\n", search(inputs[0], 3));
    // fmt::print("{}\n", search(inputs[1], 15));
    fmt::print("{}\n", search(inputs[2], 3));
}