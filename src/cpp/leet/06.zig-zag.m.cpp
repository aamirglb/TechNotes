// The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

#include <iostream>
#include <string>

using namespace std;

string convert(string s, int numRows) {
    if(numRows == 1) return s;

    string ans = "";

    for(int row = 0; row < numRows; ++row) {
        auto inc = 2 * (numRows - 1);

        for(int i = row; i < s.size(); i+=inc) {
            ans += s[i];

            if(row > 0 && row < numRows - 1) {
                auto idx = i + inc - 2 * row;
                if(idx < s.size()) {
                    ans += s[idx];
                }
            }
        }
    }
    return ans;
}

int main()
{
    string s = "PAYPALISHIRING";
    int32_t numRows = 3;

    cout << convert(s, numRows) << endl;
}