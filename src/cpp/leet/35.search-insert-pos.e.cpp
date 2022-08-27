// Given a sorted array of distinct integers and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.
// You must write an algorithm with O(log n) runtime complexity.

#include <iostream>
#include <vector>

using namespace std;

int binarySearch(vector<int>& nums, int target) {
    int low = 0;
    int high = nums.size()-1;

    while(low <= high) {
        // int mid = (low + high) / 2;
        int32_t mid = low + (high - low) / 2;
        if(nums[mid] == target) {
            return mid;
        } else if(target < nums[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return low;
}

int searchInsert(vector<int>& nums, int target) {

    auto itr = std::find(nums.begin(), nums.end(), target);
    if(itr == nums.end()) {
        itr = std::lower_bound(nums.begin(), nums.end(), target);
    }
    return std::distance(nums.begin(), itr);

    // Solution-2
    //return binarySearch(nums, target);


    // return binarySearch(nums, target);
    // if(target < nums[0]) return 0;
    // if(target > nums[ nums.size() - 1] ) return nums.size();

    // for(size_t i = 0; i < nums.size(); ++i) {
    //     if(target == nums[i]) return i;
    //     else if(nums[i] < target && nums[i+1] > target) return i+1;
    //     // if(target  nums[i]) return i+1;
    // }
}

int main()
{
    cout << "TC-1\n";
    vector<int> v {1, 2, 5, 6, 8, 10};
    int target {13};
    cout << searchInsert(v, target);

    cout << "TC-2\n";
    vector<int> v2 {1, 3};
    target = 2;
    cout << searchInsert(v2, target);

}