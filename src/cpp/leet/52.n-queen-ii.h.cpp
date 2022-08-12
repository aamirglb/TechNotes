// The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other.
// Given an integer n, return the number of distinct solutions to the n-queens puzzle.

#include <iostream>
#include <set>

using namespace std;

set<int> cols;
set<int> posDiag;
set<int> negDiag;


bool isSafe(int r, int c) {
    if(cols.find(c) == cols.end() &&
        posDiag.find(r+c) == posDiag.end() &&
        negDiag.find(r-c) == negDiag.end()) {
        return true;
    } else {
        return false;
    }
}

void backtracking(int n, int r, int &solCnt) {
    if(n == r) {
        ++solCnt;
        return;
    }

    for(int c = 0; c < n; ++c) {
        if(isSafe(r, c)) {
            cols.insert(c);
            posDiag.insert(r+c);
            negDiag.insert(r-c);

            // solve for the next queen
            backtracking(n, r+1, solCnt);

            cols.erase(c);
            posDiag.erase(r+c);
            negDiag.erase(r-c);
        }
    }
}

int totalNQueens(int n) {
    int solCnt {};
    backtracking(n, 0, solCnt);
    return solCnt;
}

int main() {
    for(int i = 1; i < 10; ++i) {
        cout << "n = " << i << " => " << totalNQueens(i) << endl;
    }
}