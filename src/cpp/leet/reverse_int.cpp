#include <iostream>
#include <limits>
#include <iomanip>

using namespace std;

int reverse(int x) {
    int maxInt = numeric_limits<int>::max();
    int minInt = numeric_limits<int>::min();

    if(x>= maxInt || x <= minInt)
        return 0;

    bool isNegative {false};

    if(x < 0) {
        x *= -1;
        isNegative = true;
    }

    long long int ans = 0;

    while( x != 0) {
        ans = (ans * 10) + (x % 10);
        cout << dec << ans << " -- " << hex << ans << endl;
        x /= 10;
    }

    if(isNegative) {
        return ans * -1;
    } else {
        return ans;
    }
}

int main()
{
    int a = 1534236469;
    cout << "max int: " << dec << numeric_limits<int>::max() << " -- " << hex << numeric_limits<int>::max() << endl;
    cout << "min int: " << dec << numeric_limits<int>::min() << " -- " << hex << numeric_limits<int>::min() << endl;
    cout << "sizeof int: " << dec << sizeof(int) << endl;
    cout << "input: " << a << " -- " << hex << a << dec << endl;
    reverse(a);
}