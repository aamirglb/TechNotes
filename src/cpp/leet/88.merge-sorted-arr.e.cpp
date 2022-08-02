#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    copy(nums2.begin(), nums2.end(), nums1.begin()+m);
    for(auto &e : nums1) cout << e << ' '; cout <<endl;
    sort(nums1.begin(), nums1.end());
}

int main()
{
    vector<int> nums1 {1, 2, 3, 0, 0, 0};
    int m = 3;
    vector<int> nums2 {2, 5, 6};
    int n = 3;

    merge(nums1, 3, nums2, n);
    copy(nums1.begin(), nums1.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}