#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;
string UncommonChars(string A, string B)
{
    map<char, int> m;
    vector<char> result;

    for(int i = 0; i < A.size(); ++i) m[ A[i] ]++;
    for(int i = 0; i < B.size(); ++i) m[ B[i] ]++;

    map<char, int>::iterator itr;
    for(itr = m.begin(); itr != m.end(); ++itr) {
        if(itr->second == 1) result.push_back(itr->first);

        std::cout << itr->first << " : " << itr->second << std::endl;
    }

    if(result.size() > 0) {
        sort(result.begin(), result.end());
        string s(result.begin(), result.end());
        return s;
    } else {
        return string("-1");
    }
}

int main()
{
    std::string a = "characters";
    std::string b = "alphabets";

    // std::cout << UncommonChars(a, b) << std::endl;

     vector<string> alphabets = {
        {"ABC"},
        {"DEF"},
        {"GHI"},
        {"JKL"},
        {"MNO"},
        {"PQRS"},
        {"TUV"},
        {"WXYZ"},
    };

    map<char, pair<int, int>> m;
    for(int i = 0; i < alphabets.size(); ++i) {
        string s = alphabets[i];
        for(int j = 0; j < s.size(); ++j) {
            m[ s[j] ] = pair<int, int>(i+2, j+1);
        }
    }

    // for(const auto& [k, v] : m) {
    //     std::cout << k << ": " << v.first << " " << v.second << std::endl;
    // }

    // string s = "GFG";
    // map<char, pair<int, int>>::iterator itr;
    // string result;
    // for(int i = 0; i < s.size(); ++i) {
    //     itr = m.find(s[i]);
    //     pair<int, int> p = itr->second;
    //     std::cout << p.first << " - " << p.second << std::endl;
    //     for(int j = 0; j < p.second; ++j)
    //         result.push_back(p.first);
    //     std::cout << result;
    // }
    if(0)
    {
        int n = 34;
        int d = 2;
        int mask = 1;
        int s = sizeof(int) * 8;
        for(int i = 1; i < d; ++i) mask = mask | (1 << i);
        int left_mask = mask << (s - d);

        int right_reminder = (n & mask) << (s - d);
        int left_reminder = (n & left_mask) >> (s - d);


        std::cout << "lt rem: " << left_reminder << std::endl;
        std::cout << "rt rem: " << right_reminder << std::endl;

        std::cout << "** " << (n << d) << std::endl;
        int left = (n << d) | left_reminder;
        int right = (n >> d) | right_reminder;

        std::cout << left << std::endl;
        std::cout << right << std::endl;
    }

    if(1)
    {
        stack<char> s;
        string x = "{([])";
        for(int i = 0; i < x.size(); ++i) {
            switch(x[i]) {
                case '(':
                    s.push(x[i]); break;
                case '{':
                    s.push(x[i]); break;
                case '[':
                    s.push(x[i]); break;
                case ')':
                    if(s.top() == '(') s.pop();
                    else s.push(x[i]);
                    break;
                case '}':
                    if(s.top() == '{') s.pop();
                    else s.push(x[i]);
                    break;
                case ']':
                    if(s.top() == '[') s.pop();
                    else s.push(x[i]);
                    break;
            }
        }
        std::cout << s.empty() << std::endl;
    }
}