// Given a string s, return the number of segments in the string.
// A segment is defined to be a contiguous sequence of non-space characters.
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fmt/format.h>
using namespace std;

int countSegments(string s) {
    if(s.empty()) return 0;
    int count{};
    istringstream iss{s};
    string tmp;
    while(iss >> tmp) ++count;
    return count;
}

int main() {
    vector<string> inputs {
        "Hello, my name is aamir",
    };
    fmt::print("{}\n", countSegments(inputs[0]));
}

