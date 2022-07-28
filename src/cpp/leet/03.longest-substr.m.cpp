// Given a string s, find the length of the longest substring without repeating characters.

#include <iostream>
#include <string>
#include <map>
using namespace std;

int lengthOfLongestSubstring(string s) {
    map<char, int> m;
    int tmpCurr = 0;
    int max = 0;
    for(int i = 0; i < s.size(); ++i) {
        if(m.count( s[i] ) > 0) {
            int tmp = m[ s[i] ];
            if( tmp >= tmpCurr) tmpCurr = tmp;
        }
        if(i+1 - tmpCurr > max) {
            max = i -tmpCurr + 1;
        }
        m[ s[i] ] = i + 1;
    }
    return max;

    // int maxLen = 0;

    // // take a map of char and index pos
    // map<char, int> m;

    // int i = 0;

    // while(i < s.size()) {

    //     if( m.count( s[i] ) == 0 ) {
    //         m[ s[i] ] = i;
    //         } else {
    //         // found a repeating char
    //         if(m.size() > maxLen) {
    //             maxLen = m.size();
    //         }
    //         // copy over char from first repeating char to current char
    //         auto start = m[ s[i] ] + 1;
    //         m.clear();
    //         for(int j = start; j <= i; ++j)
    //             m[ s[j] ] = j;
    //     }
    //     ++i;
    // }
    // if(m.size() > maxLen) maxLen = m.size();
    // return maxLen;
}