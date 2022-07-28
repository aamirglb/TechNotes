// Given two strings needle and haystack, return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int strStr(string haystack, string needle) {
    if(haystack.empty()) return 0;
    if(needle.size() > haystack.size()) return -1;

    size_t len = needle.size();

    for(size_t i = 0; i <= (haystack.size() - len); ++i)
    {
        if(haystack[i] == needle[0]) {
            if(haystack.substr(i, len) == needle) return i;
        }

    }
    return -1;
}

int main()
{
    // vector<int> v(10) = {
    //     1, 2, 3, 4, 5, 6, 7, 8, 9, 10
    // };

    // vector<string> v(2);
    // v.push_back({"hello", "ll"});
    // v.push_back({"aa", "bbbbb"});


    vector<vector<string>> input(3, vector<string>(2));
    // int i = 0;
    // for(auto s : v) input[i++] = s;
    // input.push_back(v);
    input[0] =  {"hello", "ll"};
    input[1] =  {"aaaa", "bbbba"};
    input[2] =  {"goodbye", "bye"};


    for(const auto& v : input) {
        cout << v[0] << " - " << v[1] << " : ";
        cout << strStr(v[0], v[1]) << endl;
    }

    // string a = "hello";
    // string b = "ll";

    // cout << strStr(a, b) << endl;
}