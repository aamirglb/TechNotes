#include <string>
#include <fmt/format.h>
using namespace std;

string countAndSay(int n) {
    if(n == 1) return "1";

    string s = countAndSay(n - 1);

    int freq {};
    string res {};
    for(size_t i {}; i < s.length(); ++i) {
        ++freq;
        if(i == s.length() - 1 || s[i] != s[i+1]) {
            res += to_string(freq) + s[i];
            freq = 0;
        }
    }
    return res;
}

int main() {
    for(int i = 1; i < 13; ++i) {
        fmt::print("n = {}, {}\n", i, countAndSay(i));
    }
}

