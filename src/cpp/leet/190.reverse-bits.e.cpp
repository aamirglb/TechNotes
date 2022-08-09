// Reverse bits of a given 32 bits unsigned integer.

#include <iostream>
#include <bitset>

using namespace std;

uint32_t reverseBits(uint32_t n) {
    uint32_t ans {};

    for(int32_t i = 0; i < 31; ++i) {
        // get the first bit
        auto firstBit = n & 0x1;
        ans = ans | firstBit;
        n = n >> 1;
        // make room for next bit
        if(i < 31)
            ans = ans << 1;
    }
    // cout << ans << endl;
    return ans;
}

int main() {
    uint32_t a = 43261596;
    // uint32_t b = 4294967293;
    // uint32_t a = 11;
    cout << bitset<32>(a) << endl;
    cout << bitset<32>(reverseBits(a)) << endl;

}