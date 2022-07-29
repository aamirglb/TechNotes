// Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>

using namespace std;

void backtrack(string s, int n, int openCnt, int closeCnt, vector<string> &res) {
    if(openCnt == closeCnt && openCnt == n) {
        res.push_back(s);
    }

    string str;
    if(openCnt < n) {
        backtrack(s + "(", n, openCnt+1, closeCnt, res);
    }

    if(closeCnt < openCnt) {
        backtrack(s + ")", n, openCnt, closeCnt + 1, res);
    }
}

vector<string> generateParenthesis(int n) {
    vector<string> result;
    backtrack("", n, 0, 0, result);
    return result;
}

// bool isValid(string s) {
//     stack<char> stk;
//     for(size_t i = 0; i < s.length(); ++i) {
//         if(s[i] == '(') stk.push(s[i]);
//         else {
//             if(stk.empty()) return false;
//             stk.pop();
//         }
//     }
//     return stk.empty();
// }

// vector<string> generateParenthesis(int n) {
//     vector<char> all;
//     for(int i = 0; i < n; ++i) {
//         all.push_back('(');
//         all.push_back(')');
//     }

//     do {
//         string permutation(all.begin(), all.end());
//         cout << permutation << " -- " << boolalpha << isValid(permutation) << endl;
//         // for(const auto &c : all) cout << c;
//         // cout << endl;
//     } while(next_permutation(all.begin(), all.end()));

//     return vector<string>{};
// }

int main()
{
    cout << "TC-1: n = 3\n";
    auto res = generateParenthesis(3);
    for(auto const& r : res) cout << r << endl;

    cout << "TC-2: n = 1\n";
    res = generateParenthesis(1);
    for(auto const& r : res) cout << r << endl;

    cout << "TC-2: n = 2\n";
    res = generateParenthesis(2);
    for(auto const& r : res) cout << r << endl;

}