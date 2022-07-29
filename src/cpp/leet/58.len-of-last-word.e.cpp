// Given a string s consisting of words and spaces, return the length of the last word in the string.
// A word is a maximal substring consisting of non-space characters only.

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

int lengthOfLastWord(string s) {
    reverse(s.begin(), s.end());
    istringstream ss(s);
    string last;
    ss >> last;
    return last.length();

    // if(s.find(' ') == string::npos)
    //     return s.length();

    // int i = s.size() - 1;

    // // get rid of trailing whitespaces
    // while(s[i] == ' ') --i;
    // int j = i;
    // while(j >=0 && s[j] != ' ') {
    //     --j;
    // }
    // return i - j;
}

int main()
{
    vector<string> inputs {
        "Hello World",
        "   fly me   to   the moon  ",
        "luffy is still joyboy",
        "a",
        "a ",
        " ba  ",
        "day    ",
    };

    for(const auto& input : inputs) {
        cout << input << " => " << lengthOfLastWord(input) << endl;
    }
}