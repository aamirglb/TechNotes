// Write a function that takes an unsigned integer and returns the number of '1' bits it has (also known as the Hamming weight).

#include <iostream>

using namespace std;

int hammingWeight(uint32_t n) {
    int ans {};
    for(int32_t i = 0; i < 32; ++i) {
        if( (n & 0x1) == 0x1) ++ans;
        n = n >> 1;
    }
    return ans;
}

int main() {
    uint32_t a = 11;
    cout << a << " - " << hammingWeight(a) << endl;

    uint32_t b = 1;
    cout << b << " - " << hammingWeight(b) << endl;

    uint32_t c = 0xFFFFFFFE;
    cout << c << " - " << hammingWeight(c) << endl;

    uint32_t d = 0x0;
    cout << d << " - " << hammingWeight(d) << endl;

}