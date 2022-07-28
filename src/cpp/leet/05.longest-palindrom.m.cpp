#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
/*
Test Cases Passed:
20 /123
For Input:
ayaxzfbjbkrxiri
Your Code's output is:
iri
It's Correct output is:
aya
Output Difference
iriaya


Test Cases Passed:
48 /123
For Input:
kjqlrzzfmlvyoshiktodnsjjp
Your Code's output is:
jj
It's Correct output is:
zz
Output Difference
jjzz

*/
using namespace std;

std::string center(bool input, int width = string(" false ").size()) {
    string s = "false";
    if(input) s = " true";
    return std::string((width - s.length()) / 2, ' ') + s;
}

template<typename T>
void printTable(const T &t, size_t row, size_t col)
{
    for(size_t i = 0; i < row; ++i) {
        for(size_t j = 0; j < col; ++j) {
            std::cout << std::boolalpha << center(t[i][j]);
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

std::string longest_palindrome(std::string_view str) {
    size_t len = str.size();
    size_t maxLen = 1;
    size_t start = 0;
    vector<vector<bool>> table(len, vector<bool>(len, false));
    // printTable(table, len, len);

    // find len 1 and len 2 substring
    for(size_t i = 0; i < len-1; ++i) {
        table[i][i] = true;
        if(str[i] == str[i+1]) {
            table[i][i+1] = true;
            if(maxLen == 1) {
                start = i;
                maxLen = 2;
            }
        }
    }
    table[len-1][len-1] = true;

    for(size_t m = 3; m <= len; ++m) {
        for(size_t i = 0; i < len - m + 1; ++i) {
            size_t j = i + m - 1;
            if(str[i] == str[j] && table[i+1][j-1] == true) {
                table[i][j] = true;
                if(maxLen < m) {
                    start = i;
                    maxLen = m;
                }
            }
        }
    }
    // printTable(table, len, len);
    return string(str.substr(start, maxLen));
}

int main()
{
    string s="kjqlrzzfmlvyoshiktodnsjjp";
    std::cout << longest_palindrome(s);
}