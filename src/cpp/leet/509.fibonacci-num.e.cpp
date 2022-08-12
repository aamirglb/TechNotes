#include <iostream>
#include <unordered_map>
using namespace std;

int fibWithMemo(int n, unordered_map<int, int> &memo) {
    if(n < 2) return n;

    if(memo.find(n) != memo.end()) return memo[n];

    memo[n] = fibWithMemo(n - 1, memo) + fibWithMemo(n - 2, memo);
    return memo[n];
}

int fib(int n) {
    unordered_map<int, int> memo;
    return fibWithMemo(n, memo);
}

// constant memory solution
int fibConst(int n) {
    int f1 = 0;
    int f2 = 1;

    if(n == 0) return 0;
    for(int i = 1; i < n; ++i) {
        auto tmp = f1;
        f1 = f2;
        f2 = tmp + f2;
    }
    return f2;
}
int main() {
    cout << fib(10) << endl;
    cout << fib(20) << endl;
    cout << fib(30) << endl;

    cout << fibConst(10) << endl;
    cout << fibConst(20) << endl;
    cout << fibConst(30) << endl;
}