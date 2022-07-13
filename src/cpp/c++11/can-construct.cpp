#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <iomanip>

using namespace std;
bool canConstruct(string target, vector<string> wordBank, map<string, bool> &memo)
{
    if(memo.find(target) != memo.end()) return memo[target];

    if(target.empty()) return true;

    for(const auto &word : wordBank) {
        if(target.find(word) == 0) {
            string suffix = target.substr(word.size());
            if(canConstruct(suffix, wordBank, memo)) {
                memo[target] = true;
                return true;
            }
        }
    }
    memo[target] = false;
    return false;
}

int32_t countConstruct(string target, vector<string> wordBank, map<string, int32_t> &memo) {

    if(memo.find(target) != memo.end()) return memo[target];

    if(target.empty()) return 1;

    int32_t totalCount{};
    for(const auto &word : wordBank) {
        if(target.find(word) == 0) {
            string suffix = target.substr(word.size());
            totalCount += countConstruct(suffix, wordBank, memo);
        }
    }
    memo[target] = totalCount;
    return memo[target];
}
int main()
{
    vector<string> a = {
        "abcdef",
        "skateboard",
        "enterapotentpot",
        "eeeeeeeeeeeeeeeeeeeeeeeeeeeef",
        "visual",
        "purple",
    };

    vector<vector<string>> v {
        { "ab", "abc", "cd", "def", "abcd", },
        { "bo", "rd", "ate", "t", "ska", "sk", "boar"},
        { "a", "p", "ent", "enter", "ot", "o", "t"},
        { "e", "ee", "eee", "eeee", "eeeee", "eeeeee"},
        { "al", "vi", "eal", "su", "vis", "ual", "sia"},
        {"purp", "p", "ur", "le", "purpl"},
    };

    map<string, bool> memo;
    map<string, int32_t> memo2;
    for(size_t i = 0; i < a.size(); ++i) {
        memo.clear();
        std::cout << boolalpha << canConstruct(a[i], v[i], memo); // << std::endl;
        memo2.clear();
        std::cout << "  " << countConstruct(a[i], v[i], memo2) << std::endl;

        // for(const auto& [k, v] : memo) {
        //     std::cout << k << " : " << v << endl;
        // }
    }

    // string b = "abc";
    // string c = "bce";

    // auto itr = find_first_of(c.begin(), c.end(), a.begin(), a.end());
    // if(itr == c.begin()) {
    //     cout << "b is a prefix\n";
    // }
}