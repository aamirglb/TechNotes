// You are given a large integer represented as an integer array digits, where each digits[i] is the ith digit of the integer. The digits are ordered from most significant to least significant in left-to-right order. The large integer does not contain any leading 0's.

#include <iostream>
#include <vector>

using namespace std;

vector<int> plusOne(vector<int>& digits) {
    size_t n = digits.size();

    if(digits[n-1] < 9) {
        digits[n-1]++;
        return digits;
    } else {

        vector<int> res(n);
        int carry = 1;
        for(int i = n-1; i>=0; --i) {
            res[i] = (digits[i] + carry) % 10;
            carry = (digits[i] + carry) / 10;
        }
        if(carry > 0) res.insert(res.begin(), carry);
        return res;
    }
}

int main()
{
    cout << "TC-1\n";
    vector<int> v {1, 2, 3};
    auto r1 = plusOne(v);
    for(const auto &e : r1) cout << e;
    cout << endl;

    cout << "TC-2\n";
    vector<int> v1 {9};
    auto r2 = plusOne(v1);
    for(const auto &e : r2) cout << e;
    cout << endl;

    cout << "TC-3\n";
    vector<int> v2 {8, 9, 9, 9};
    auto r3 = plusOne(v2);
    for(const auto &e : r3) cout << e;
    cout << endl;

}