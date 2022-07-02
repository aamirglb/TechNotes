/*
Reverse array in groups
Basic Accuracy: 51.16% Submissions: 94949 Points: 1
Lamp
This problem is part of GFG SDE Sheet. Click here to view more.
Given an array arr[] of positive integers of size N. Reverse every sub-array group of size K.



Example 1:

Input:
N = 5, K = 3
arr[] = {1,2,3,4,5}
Output: 3 2 1 5 4
Explanation: First group consists of elements
1, 2, 3. Second group consists of 4,5.


Example 2:

Input:
N = 4, K = 3
arr[] = {5,6,8,9}
Output: 8 6 5 9
*/
#include <iostream>
#include <vector>

template <typename T>
void swap(T &a, T &b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

void reverseInGroups(std::vector<long long>& arr, int n, int k){

    std::cout << "n = " << n << " k = " << k << " n/k = " << n/k << " n % k = " << n % k << std::endl;
    long long c;
    for(c = 0; c < n/k; ++c) {
        std::cout << " i = " << (c*k) << " j = " << ((c+1)*k) - 1 << std::endl;
        for(long long i = (c*k), j = ((c+1)*k) - 1; i < j; i++, j--) {
            swap<long long>(arr[i], arr[j]);
        }
    }
    std::cout << (k*c) << std::endl;
    for(long long i = (k*c), j = n - 1; i < j; ++i, --j)
    swap<long long>(arr[i], arr[j]);
}

int main()
{
    std::vector<long long> arr {1,2,3,4,5,6,7,8,9,10,11,12};
    int n = 12, k = 3;

    reverseInGroups(arr, n, k);
    std::cout << "Expected: 3 2 1 6 5 4 9 8 7 11 10" << std::endl;
    std::cout << "Actual:   ";
    for(const auto &e : arr) {
        std::cout << e << ' ';
    }
    std::cout << std::endl;
}