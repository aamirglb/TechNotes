// Given an integer columnNumber, return its corresponding column title as it appears in an Excel sheet.

#include <iostream>
#include <string>

using namespace std;

string convertToTitle(int columnNumber) {
    string res {};
    while(columnNumber) {
        char ch = 'A' + (columnNumber - 1) % 26;
        res = string(1, ch) + res;
        columnNumber = (columnNumber - 1) / 26;
    }
    return res;
}

int main() {
    for(int i=1; i<=28; ++i) cout << convertToTitle(i) << " ";
    cout << "\n" << convertToTitle(701) << endl;
}