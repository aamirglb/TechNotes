// Implement pow(x, n), which calculates x raised to the power n (i.e., xn).

#include <iostream>
#include <cmath>
#include <vector>

// Solution should not have time complexity of O(n)
// It should be O(log n)

using namespace std;

// double power(double x, int n) {
//     if(x == 0) return 0;
//     if(n == 0) return 1;
//     return x * power(x, n-1);
// }

// double myPow(double x, int n) {
//     long double ans {1};

//     if(n%2 == 0)
//         ans = power(x*x, abs(n)/2);
//     else {
//         ans = power(x, abs(n)/2);
//         ans *= ans;
//         ans *= x;
//     }
//     if(n > 0) return ans;
//     else return 1/ans;
    // for(auto i = 0; i < abs(n)/2; ++i) {
    //     ans = ans * x;
    // }
    // ans *= ans;
    // if(abs(n) % 2 != 0) ans *= x;
    // if(n < 0) ans = 1.0 / ans;
    // return ans;
// }


double power(double x, int n) {
    if(x == 0) return 0;
    if(n == 0) return 1;
    double res = power(x, n/2);
    res *= res;
    return n%2 ? x * res : res;
}

double myPow(double x, int n) {
    double res = power(x, abs(n));
    return n>=0 ? res : 1/res;
}

int main()
{
    vector<double> xs { 2.0, 2.1, 2.0, 1.0, };
    vector<int> ns    {10, 3, -2, 2147483647};

    for(size_t i = 0; i < xs.size(); ++i) {
        cout << xs[i] << "^" << ns[i] << " = " << myPow(xs[i], ns[i]) << endl;
    }

}
