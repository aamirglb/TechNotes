// Given two strings s and t, determine if they are isomorphic.
// Two strings s and t are isomorphic if the characters in s can be replaced to get t.

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;


bool isIsomorphic(string s, string t) {
    if(s.length() != t.length()) return false;
    unordered_map<char, char> smap;
    unordered_map<char, char> tmap;

    for(size_t i = 0; i < s.length(); ++i) {
        auto c1 = s[i];
        auto c2 = t[i];

        if(smap.count(c1) > 0 && smap[c1] != c2)
            return false;

        if(tmap.count(c2) > 0 && tmap[c2] != c1)
            return false;

        smap[c1] = c2;
        tmap[c2] = c1;
    }
    return true;
}

int main() {
    cout << boolalpha << isIsomorphic("egg", "add") << endl;
    cout << boolalpha << isIsomorphic("foo", "bar") << endl;
}