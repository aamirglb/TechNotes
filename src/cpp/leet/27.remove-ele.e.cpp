// Given an integer array nums and an integer val, remove all occurrences of val in nums in-place. The relative order of the elements may be changed.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int removeElement(vector<int>& nums, int val) {
    // auto last = remove_if(nums.begin(), nums.end(), [=](int ele) { return val == ele;} );
    // return last - nums.begin();

    int j{0};
    for(size_t i = 0; i < nums.size(); ++i) {
        if(nums[i] != val) {
            nums[j++] = nums[i];
        }
    }
    return j;
}

int main()
{
    vector<int> input {
        2,0,1,2,2,3,0,4,2
    };

    for(auto & e : input) cout << e << ' ';
    cout << endl;
    cout << removeElement(input, 2) << endl;

    for(auto & e : input) cout << e << ' ';
    cout << endl;
}