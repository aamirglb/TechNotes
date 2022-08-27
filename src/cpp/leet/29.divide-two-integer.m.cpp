// Given two integers dividend and divisor, divide two integers without using multiplication, division, and mod operator.
#include <fmt/format.h>
using namespace std;

 int divide(int dividend, int divisor) {
     if(dividend==numeric_limits<int>::min() && divisor==-1) return numeric_limits<int>::max();
    if(dividend==numeric_limits<int>::min() && divisor==1) return numeric_limits<int>::min();

    bool sign = (dividend >= 0) == (divisor >= 0) ? true : false;

    long di = abs(dividend);
    long dv = abs(divisor);

    long ans {};
    while(di - dv >= 0) {
        int count {};
        while(di - (dv << (1 << count)) >= 0) ++count;
        ans += (1 << count);
        di -= (dv << count);
    }
    return sign ? ans : -ans;
 }

int main() {
    fmt::print("{}\n", divide(10, 3));
}