// Write a function to find the longest common prefix string amongst an array of strings.
// If there is no common prefix, return an empty string "".

#include <string>
#include <iostream>
#include <vector>

using namespace std;

string longestCommonPrefix(vector<string>& strs) {
    string res{};

    for(size_t i = 0; i < strs[0].length(); ++i) {
        // loop through all remaining strings
        for(size_t j = 1; j < strs.size(); ++j) {
        // for(const auto &s : strs) {
            if( strs[j].length() == i || strs[j][i] != strs[0][i]) {
                return res;
            }
        }
        res.push_back(strs[0][i]);
    }
    return res;
}

int main()
{
    vector<vector<string>> input {{
        "geeksforgeeks",
        "geeks",
        "geek",
        "geezer",
    },
    {
         "flower",
         "flow",
         "flight",
    },
    {
        "dog",
        "racecar",
        "car"
    }};

    for(size_t i = 0; i < input.size(); ++i) {
        cout << longestCommonPrefix(input[i]) << endl;
    }
}