// You are given a string s and an array of strings words. All the strings of words are of the same length.
// A concatenated substring in s is a substring that contains all the strings of any permutation of words concatenated.
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fmt/format.h>
#include <fmt/ranges.h>
using namespace std;

vector<int> findSubstring(string s, vector<string>& words) {
    vector<int> res;
    unordered_map<string, int> m;
    for(const auto& word : words) m[word]++;
    size_t n = words[0].length();

    if(s.length() < words.size() * n) return {};

    for(size_t i = 0; i <= (s.length() - (words.size() * n)); ++i) {
        unordered_map<string, int> tmp = m;
        auto j = i;
        while(!tmp.empty()) {
            string sub = s.substr(j, n);
            // found the substring
            if(tmp.find(sub) != tmp.end()) {
                tmp[sub]--;
                if(tmp[sub] == 0) tmp.erase(sub);
                j += n;
            } else {
                break;
            }
        }
        if(tmp.empty()) res.push_back(i);
    }
    return res;
}

vector<int> findSubstringV2(string s, vector<string>& words) {
    int wordsquan = words.size();
    int wordsleng = words[0].size();
    int target = wordsquan * wordsleng;
    unordered_map<string, int> unmap;

    for (int j = 0; j < wordsquan; j++)
    {
        unmap[words[j]]++;
    }
    vector<int> ans;
    if (s.size() < target)
    {
        return ans;
    }
    for (int i = 0; i <= s.size() - target; i++)
    {
        unordered_map<string, int> unmap2;
        unmap2 = unmap;
        int k;
        for (k = 0; k < wordsquan; k++)
        {
            string s1 = s.substr(i + k * wordsleng, wordsleng);
            if (unmap2.count(s1) == 0)
                break;
            else if (unmap2[s1] != 0)
                unmap2[s1]--;
            else
                break;
        }
        fmt::print("k = {}, {}\n", k, wordsquan);
        if (k == wordsquan)
        {
            ans.push_back(i);
        }
    }
    fmt::print("ans: {}\n", ans);
    return ans;
}

int main() {
    // string s = "barfoothefoobarman";
    // vector<string> words {"foo","bar"};
    // findSubstring(s, words);

    // string s1 = "wordgoodgoodgoodbestword";
    // vector<string> words1 {"word","good","best","word"};
    // findSubstring(s1, words1);

    // string s2 = "barfoofoobarthefoobarman";
    // vector<string> words2 {"bar","foo","the"};
    // findSubstring(s2, words2);

    string s3 = "wordgoodgoodgoodbestword";
    vector<string> words3 {"word","good","best","word"};
    // findSubstring(s3, words3);
    findSubstringV2(s3, words3);
}