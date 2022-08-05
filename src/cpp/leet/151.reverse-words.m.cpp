// Given an input string s, reverse the order of the words.

#include <iostream>
#include <string>
#include <stack>
#include <sstream>

using namespace std;

string reverseWords(string s) {

    stack<string> stk;
    stringstream ss(s);
    string word;
    string result;
    while(ss >> word) stk.push(word);
    while(!stk.empty()) {
        result += stk.top() + ' ';
        stk.pop();
    }
    result.pop_back();
    return result;
}

int main()
{
    string s = "the sky is blue";
    cout << reverseWords(s) << endl;

}