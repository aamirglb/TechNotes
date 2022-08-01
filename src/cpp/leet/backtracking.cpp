// given an input string, find all possible combination
#include <iostream>
#include <string>
#include <vector>
#include <numeric>

using namespace std;

// void backtracking(string s) {
//     if(s.length() == 3) {
//         cout << s << endl;
//         return;
//     } else {
//         backtracking()
//     }
// }

// void generateCombination(string s)
// {
//     for(const char &c : s) {
//         backtracking(c);
//     }
// }

// bounding functions for killing the extra nodes
// if total weight sofar should be  sum <= m
// if total sum and remaining sum > sum

void backtracking(const vector<int> &v, int idx, int target, int sum)
{
    if(idx == 0 && target == sum) {

    }
}
void sumOfSubset(const vector<int> &v, int target)
{
    int total = accumulate(v.begin(), v.end(), 0);
    for(size_t i = 0; i < v.size(); ++i) {
        backtracking(v, target);
    }
}
int main()
{
    vector<int> v {5, 10, 12, 13, 15, 18};
    int targetSum = 30;
}