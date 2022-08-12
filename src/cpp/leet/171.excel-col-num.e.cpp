// Given a string columnTitle that represents the column title as appears in an Excel sheet, return its corresponding column number.

#include <iostream>
#include <string>
using namespace std;

int titleToNumber(string columnTitle) {
    int res {};
    int factor {1};
    int n = columnTitle.length() - 1;

    while(n >= 0) {
        auto digit = columnTitle[n] - 'A' + 1;
        res += (digit * factor);
        factor *= 26;
        --n;
    }
    return res;
}

int main() {
    cout << titleToNumber("AB") << endl;
    cout << titleToNumber("ZY") << endl;
}