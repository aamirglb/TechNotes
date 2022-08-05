// There is an integer array nums sorted in ascending order (with distinct values).
// Prior to being passed to your function, nums is possibly rotated at an unknown pivot index

#include <iostream>
#include <vector>

using namespace std;

int binarySearch(vector<int>& nums, int key, int low, int high) {

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

int search(vector<int>& nums, int target) {
    int pivot {};
    int sz = nums.size() - 1;
    while( (pivot < sz) && (nums[pivot] < nums[pivot+1]))
        ++pivot;

    if(target >= nums[0] && target <= nums[pivot]) {
        return binarySearch(nums, target, 0, pivot);
    } else {
        return binarySearch(nums, target, pivot+1, sz);
    }
}

int main() {
    vector<int> v1 {4,5,6,7,0,1,2};
    vector<int> keys {4, 7, 0, 2, 12};

    for(const auto& k : keys)
        cout << search(v1, k) << endl;
}
