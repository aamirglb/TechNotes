/*
Subarray with given sum
Given an unsorted array A of size N that contains only non-negative integers, find a continuous sub-array which adds to a given number S.
In case of multiple subarrays, return the subarray which comes first on moving from left to right.

Example 1:

Input:
N = 5, S = 12
A[] = {1,2,3,7,5}
Output: 2 4
Explanation: The sum of elements
from 2nd position to 4th position
is 12.

Example 2:

Input:
N = 10, S = 15
A[] = {1,2,3,4,5,6,7,8,9,10}
Output: 1 5
Explanation: The sum of elements
from 1st position to 5th position
is 15.

Constraints:
1 <= N <= 105
1 <= Ai <= 109
*/

#include <iostream>
#include <algorithm>
#include <iterator>
#include <array>

int main()
{
    int A[] = {1,2,3,4,5,6,7,8,9,10};
    // std::array<int32_t, 10> arr {1,2,3,4,5,6,7,8,9,10};
    std::array<int32_t, 74> arr {
        142, 112, 54, 69, 148, 45, 63, 158, 38, 60, 124, 142, 130, 179, 117, 36, 191, 43, 89, 107,
        41, 143, 65, 49, 47, 6, 91, 130, 171, 151, 7, 102, 194, 149, 30, 24, 85, 155, 157, 41, 167,
        177, 132, 109, 145, 40, 27, 124, 138, 139, 119, 83, 130, 142, 34, 116, 40, 59, 105, 131,
        178, 107, 74, 187, 22, 146, 125, 73, 71, 30, 178, 174, 98, 113,
    };
    int n = 74;
    long long S = 665;
    std::vector<int> result;

    long long sum = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = i; j < n; ++j) {
            sum += arr[j];
            std::cout << i << " " << j << " sum: " << sum << std::endl;
            if(sum == S) {
                std::cout << i+1 << " " << j+1 << std::endl;
                for(int k = i; k <= j; ++k) result.push_back(arr[k]);
                for(const auto& e : result) std::cout << e << " ";
                return 0;
            } else if(sum > S) {
                sum = 0;
                break;
            }
        }
    }
    std::cout << "reached end of loop with no results\n";
    // std::for_each(std::begin(A), std::end(A), [](auto e){ std::cout << e << " ";});
}