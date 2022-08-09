// You are climbing a staircase. It takes n steps to reach the top.
// Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

#include <iostream>
#include <vector>

using namespace std;

int backtracking(int n, int step, vector<int> &res) {
    if(step > n) return 0;
    if(step == n) {
        cout << "recached a solution" << endl;
        for(const auto& e : res) cout << e << ' ';
        cout << endl;
        return 1;
    }
    res.push_back(step);
    return backtracking(n, step+1, res) + backtracking(n, step+2, res);
    // return 0;
}
int climbStairs(int n) {
    int f1 = 1;
    int f2 = 1;

    for(int i = 0; i < n-1; ++i) {
        auto tmp = f1;
        f1 = f1 + f2;
        f2 = tmp;
    }
    return f1;
}

int main() {
    cout << climbStairs(5) << endl;
}