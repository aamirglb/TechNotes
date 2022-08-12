// There is a robot on an m x n grid. The robot is initially located at the top-left corner (i.e., grid[0][0]). The robot tries to move to the bottom-right corner (i.e., grid[m - 1][n - 1]). The robot can only move either down or right at any point in time.
// Given the two integers m and n, return the number of possible unique paths that the robot can take to reach the bottom-right corner.

#include <iostream>
#include <vector>
#include <map>
using namespace std;
using Cell = pair<int, int>;

int cnt {};

// int backtracking(int m, int n, int cm, int cn, string &path) {
//     if(cm == m - 1 && cn == n - 1) {
//         cout << ++cnt << ". " << path << endl;
//         return 1;
//     }

//     int x {}, y {};
//     if(cm != m - 1) {
//         path.push_back('D');
//         x = backtracking(m, n, cm+1, cn, path);
//         path.pop_back();
//     }
//     if(cn != n - 1) {
//         path.push_back('R');
//         y = backtracking(m, n, cm, cn+1, path);
//         path.pop_back();
//     }

//     return x+y;
// }

int backtracking(int m, int n, int cm, int cn, map<Cell, int> &memo) {

    Cell cell = make_pair(cm, cn);
    if(memo.find(cell) != memo.end()) return memo[cell];

    if(cm == m - 1 && cn == n - 1) {
        return 1;
    }

    int x {}, y {};
    if(cm != m - 1) {
        x = backtracking(m, n, cm+1, cn, memo);
    }
    if(cn != n - 1) {
        y = backtracking(m, n, cm, cn+1, memo);
    }

    memo[cell] = x+y;
    return memo[cell];
}

int uniquePaths(int m, int n) {
    string path;
    map<Cell, int> memo;
    map<Cell, string> pathMemo;
    // return backtracking(m, n, 0, 0, path);
    return backtracking(m, n, 0, 0, memo);
}

int main() {
    cout << uniquePaths(19, 13) << endl;
}