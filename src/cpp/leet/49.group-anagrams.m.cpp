// Given an array of strings strs, group the anagrams together. You can return the answer in any order.
// An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all the original letters exactly once.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <array>
#include <map>
#include <fmt/format.h>
#include <fmt/ranges.h>
using namespace std;

vector<vector<string>> groupAnagrams(vector<string>& strs) {
    if(strs.size() == 0) return {};
    if(strs.size() < 2) return {strs};


    map<array<int, 26>, vector<string>> m;
    vector<vector<string>> res;

    // string s = "aabccdddddde";
    // string s2 = "bddddddeccaa";
    // array<int, 6> a {}, b{};
    // for(auto& c : s) a[c-'a'] += 1;
    // for(auto& c : s2) b[c-'a'] += 1;

    // for(auto &i : a) fmt::print("{}, ", i); fmt::print("\n");
    // for(auto &i : b) fmt::print("{}, ", i);
    // fmt::print("\n{}\n", a == b);

    for(const auto& s : strs) {
        array<int, 26> count {};
        for(const auto& c : s) {
            count[c - 'a'] += 1;
        }

        m[count].push_back(s);
    }

    for(auto& [_, v] : m) {
            res.push_back(v);
            fmt::print("{}\n", v);
    }
    return res;
}

int main() {
    vector<string> strs1 {""};
    vector<string> strs2 {"a"};
    vector<string> strs3 {"eat","tea","tan","ate","nat","bat"};
    groupAnagrams(strs3);
}