// Given a string s, find the first non-repeating character in it and return its index. If it does not exist, return -1.

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

int firstUniqChar(string s) {
    unordered_map<char, int> m;
    for(const auto& c: s) {
        m[c]++;
    }

    // iteratre the string from 0..len-1
    for(size_t i = 0; i < s.length(); ++i) {
        if(m[ s[i] ] == 1) return i;
    }
    return -1;
}

int main() {
    vector<string> inputs {
        "leetcode",
        "loveleetcode",
        "aabb",
    };

    for(auto & input : inputs ) {
        cout << input << ": " << firstUniqChar(input) << endl;
    }
}