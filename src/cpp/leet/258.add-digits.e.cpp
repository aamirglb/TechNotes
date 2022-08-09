// Given an integer num, repeatedly add all its digits until the result has only one digit, and return it.

#include <iostream>
using namespace std;

int addDigits(int num) {
    if(num == 0) return 0;

    int sum = 0;
    while(num) {
        auto d = num % 10;
        sum += d;
        num /= 10;

        if(num == 0) {
            if(sum < 10) break;
            else {
                num = sum;
                sum = 0;
            }
        }
    }
    return sum;
}

int main() {
    cout << addDigits(38) << endl;
}