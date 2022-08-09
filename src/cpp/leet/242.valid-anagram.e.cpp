// Given two strings s and t, return true if t is an anagram of s, and false otherwise.

#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

bool isAnagram(string s, string t) {
    if(s.length() != t.length()) return false;

    unordered_map<char, int> m1, m2;
    for(size_t i = 0; i < s.length(); ++i) {
        m1[ s[i] ]++;
        m2[ t[i] ]++;
    }
    return m1 == m2;
}

int main() {
    string s = "anagram";
    string t = "nagaram";

    cout << boolalpha << isAnagram(s, t) << endl;
}