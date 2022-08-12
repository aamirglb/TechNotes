// Given an array of strings strs, group the anagrams together. You can return the answer in any order.
// An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all the original letters exactly once.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<string>> groupAnagrams(vector<string>& strs) {
    if(strs.size() < 2) return {strs};

    sort(strs.begin(), strs.end());
}

int main() {
    vector<string> s1 {""};
    vector<string> s2 {"a"};

}