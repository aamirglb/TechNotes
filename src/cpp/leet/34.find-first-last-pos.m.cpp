// Given an array of integers nums sorted in non-decreasing order, find the starting and ending position of a given target value.

#include <iostream>
#include <vector>

using namespace std;

int binarySearch(vector<int>& nums, int key) {
    int low = 0;
    int high = nums.size() - 1;

    while(low <= high) {
        int mid = (low + high)/2;
        if(nums[mid] == key) return mid;
        else if(key < nums[mid] ) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return -1;
}

vector<int> searchRange(vector<int>& nums, int target) {
    vector<int> result(2, -1);

    int idx = binarySearch(nums, target);

    if(idx != -1) {
        auto tmp = idx;
        while(tmp > 0 && nums[tmp] == nums[tmp-1]) tmp--;
        result[0] = tmp;
        while(idx < nums.size() - 1 && nums[idx] == nums[idx+1])
            idx++;
        result[1] = idx;
    }
    return result;
}

int main()
{
    vector<vector<int>> inputs {
        {5,7,7,8,8,8,8,10},
        {5,7,7,8,8,10},
        {},
    };

    vector<int> targets {
        8, 6, 0,
    };

    int i = 0;
    for(auto& v : inputs) {
        auto r = searchRange(v, targets[i++]);
        cout << "[" << r[0] << ", " << r[1] << "]\n";
    }
}