// A phrase is a palindrome if, after converting all uppercase letters into lowercase letters and removing all non-alphanumeric characters, it reads the same forward and backward. Alphanumeric characters include letters and numbers.

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

bool isPalindrome(string s) {
    string r;

    for(const auto& c: s) {
        if(isalnum(c)) r.push_back(tolower(c));
    }
    if(r.empty()) return true;

    auto rr = r;
    reverse(rr.begin(), rr.end());
    return rr == r;
}

int main()
{
    string s = "A man, a plan, a canal: Panama";
    cout << boolalpha << isPalindrome(s) << endl;

    string s2 = "race a car";
    cout << boolalpha << isPalindrome(s2) << endl;
}