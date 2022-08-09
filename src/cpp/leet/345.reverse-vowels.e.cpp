// Given a string s, reverse only all the vowels in the string and return it.

#include <iostream>
#include <string>

using namespace std;

bool isVowel(char c) {
    c = tolower(c);

    if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
        return true;
    return false;
}

string reverseVowels(string s) {

    if(s.length() == 1) return s;
    size_t l = 0;
    size_t r = s.length() - 1;

    while(l < r) {
        while(l < r && !isVowel(s[l])) ++l;
        while(r > 0 && !isVowel(s[r])) --r;
        if(l < r) {
            swap(s[l], s[r]);
            ++l;
            --r;
        }
    }
    return s;
}

int main() {
    string s = "hello";
    cout << reverseVowels(s) << endl;

    s = "leetcode";
    cout << reverseVowels(s) << endl;
}