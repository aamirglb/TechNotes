// Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {

    for(const auto& e : nums2) nums1.push_back(e);
    sort(nums1.begin(), nums1.end());
    auto mid = nums1.size() / 2;
    if(nums1.size() % 2 != 0) {
        return nums1[mid];
    } else {
        return (nums1[mid-1] + nums1[mid]) / 2.;
    }

    // vector<int> result;
    // size_t i{}, j{};

    // while(i < nums1.size() && j < nums2.size()) {
    //     if(nums1[i] <= nums2[j]) {
    //         result.push_back(nums1[i++]);
    //     } else {
    //         result.push_back(nums2[j++]);
    //     }
    // }

    // while(i < nums1.size()) result.push_back(nums1[i++]);
    // while(j < nums2.size()) result.push_back(nums2[j++]);

    // auto mid = result.size() / 2;
    // if(result.size() % 2 != 0) {
    //     return result[mid];
    // } else {
    //     return (result[mid-1] + result[mid]) / 2.;
    // }
    // // for(const auto& ele : result) cout << ele << ' ';
    // // cout << endl;
}

int main()
{
    vector<int> v1 {1, 2, 4};
    vector<int> v2 {3, 4};

    cout << "Median: " << findMedianSortedArrays(v1, v2) << endl;
}