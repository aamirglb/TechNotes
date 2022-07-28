// Given an integer array nums sorted in non-decreasing order, remove the duplicates in-place such that each unique element appears only once. The relative order of the elements should be kept the same.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int removeDuplicates(vector<int>& nums) {
    // auto last = unique(nums.begin(), nums.end());
    // return last - nums.begin();

    int left = 0;

    for(size_t i = 1; i < nums.size(); ++i) {
        // check if current element is unique
        if(nums[i-1] < nums[i]) {
            nums[++left] = nums[i];
        }
    }
    return left+1;
}

int main()
{
    vector<int> input {
        0,0,1,1,1,1,1,2,2,2,3,3,4,5,6,7
    };
    for(const auto & e : input) cout << e << ' ';
    cout << endl;
    cout << removeDuplicates(input) << endl;
    for(const auto & e : input) cout << e << ' ';
    cout << "done..." << endl;
}