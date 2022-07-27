// Implement the myAtoi(string s) function, which converts a string to a 32-bit signed integer

#include <string>
#include <limits>
#include <iostream>
#include <vector>

using namespace std;

int myAtoi(string s) {
    unsigned long long int ans { 0 };
    bool isNegative { false };
    int i { 0 };

    // cout << "input: " << s ;
    // Skip leading spaces
    while(s[i] == ' ') ++i;

    if(s[i] == '-') {
        isNegative = true;
        ++i;
    }

    if(s[i] == '+') ++i;

    while(true) {
        if(!isdigit(s[i])) break;
        ans = (ans * 10) + (s[i++] - '0');
        if(ans > numeric_limits<int>::max()) break;
        cout << ans << endl;
    }
    // if(isNegative) ans = ans * (-1);

    cout << ans << endl;
    if(!isNegative && ans > numeric_limits<int>::max()) {
        return numeric_limits<int>::max();
    }

    if(isNegative) {
        if( ans  > (numeric_limits<int>::max())) {
            return numeric_limits<int>::min();
        }
    }

    // cout << "  ans: " << ans <<endl;
    if(isNegative) return (ans * -1);
    else return ans;
}

int main()
{
    vector<string> inputs {
        // "-123",
        // "  42",
        // "        -8765",
        // "-91283472332",
        // "  -0k4",
        "18446744073709551617",
    };

    // cout << (numeric_limits<int>::max()) << endl;
    // unsigned long long int ans = 0;
    // cout << (ans * -1) << ' ' <<  numeric_limits<int>::min() << endl;
    // if( (ans * -1) > numeric_limits<int>::min()) {
    //     cout << "zero less than min!!\n";
    // }
    for(const auto& s : inputs) {
        cout << s << " -- " << myAtoi(s) << endl;
    }
}