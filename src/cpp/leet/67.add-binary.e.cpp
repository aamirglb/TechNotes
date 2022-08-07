// Given two binary strings a and b, return their sum as a binary string.

#include <iostream>
#include <string>

using namespace std;

string addBinary(string a, string b) {
    size_t m = a.length();
    size_t n = b.length();

    string res(max(m, n), '0');
    size_t i = res.length();
    int carry {};
    while(m > 0 && n > 0) {
        carry = carry + (a[--m] - '0') + (b[--n] - '0');
        res[--i] = (carry % 2) + '0';
        carry /= 2;
    }
    while(m) {
        carry = carry + (a[--m] - '0');
        res[--i] = (carry % 2) + '0';
        carry /= 2;
    }
    while(n) {
        carry = carry + (b[--n] - '0');
        res[--i] = (carry % 2) + '0';
        carry /= 2;
    }
    if(carry > 0) res.insert(res.begin(), '1');
    return res;
}

int main()
{
    cout << "TC-1\n";
    string a = "11";
    string b = "1";
    cout << addBinary(a, b) << endl;

    cout << "TC-2\n";
    string c = "1010";
    string d = "1011";
    cout << addBinary(c, d) << endl;



}