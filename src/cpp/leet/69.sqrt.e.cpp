// Given a non-negative integer x, compute and return the square root of x.

#include <iostream>

using namespace std;

int mySqrt(int x) {
    if(x <= 1) return x;

    int left = 1;
    int right = x;

    while(left < right) {
        int mid = (left + right) / 2;
        int square = mid * mid;

        if(square == x) return mid;
        else if(square > x) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left - 1;
}

int main() {
    cout << mySqrt(4) << endl;
    cout << mySqrt(8) << endl;
    cout << mySqrt(16) << endl;
    cout << mySqrt(3) << endl;
}
