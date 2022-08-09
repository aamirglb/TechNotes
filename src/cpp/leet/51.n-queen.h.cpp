// The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two
// queens attack each other.
//

#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

// bool isItSafePlace(vector<vector<bool>>& board, int row, int col) {
//     // vertial up
//     int r = row -1;
//     int c = col;
//     while(r >= 0) {
//         if(board[r][c]) return false;
//         --r;
//     }

//     // horizontal left
//     r = row;
//     c = col - 1;
//     while(c >= 0) {
//         if(board[r][c]) return false;
//         --c;
//     }

//     r = row - 1;
//     c = col - 1;
//     while(r >= 0 && c >= 0) {
//         if(board[r][c]) return false;
//         --r; --c;
//     }

//     // diagonally right
//     r = row - 1;
//     c = col + 1;
//     while(r >= 0 && c < board[0].size()) {
//         if(board[r][c]) return false;
//         --r;
//         ++c;
//     }
//     return true;
// }

// int cnt {};
// void nQueen(vector<vector<bool>>& board,
//     int row,
//     int col,
//     int tq,
//     int qpsf,
//     string ans)
// {
//     if(qpsf == tq) {
//         cout << ++cnt << " => " << ans << endl;
//         return;
//     }

//     if(col == board[0].size()) {
//         ++row;
//         col = 0;
//     }
//     if(row == board[0].size()) {
//         return;
//     }

//     if(isItSafePlace(board, row, col)) {
//         // do
//         board[row][col] = true;
//         string s = "[" + to_string(row) + ", " +  to_string(col) + "]";
//         // recur
//         nQueen(board, row, col+1, tq, qpsf+1, ans + s);

//         // undo
//         board[row][col] = false;
//     }

//     nQueen(board, row, col+1, tq, qpsf, ans);

// }

// // return true if kth queen can be placed at ith column
// bool place(int k, int i, vector<int> &x) {
//     for(int j = 0; j < k-1; ++j) {
//         if(x[j] == i || abs(x[j] - i) == abs(i - k))
//             return false;
//     }
//     return true;
// }

// void nQueen(int n, int k, vector<int> &x) {
//     // Recursion with in iteration
//     for(int i = 0; i < n; ++i) {
//         if(place(k, i, x)) {
//             x[k] = i;
//             if(k == n) {
//                 cout << "k = " << k << " n = " << n << endl;
//                 for(const auto& e : x) {
//                     cout << e << ' ';
//                 }
//                 cout << endl;
//             } else {
//                 nQueen(n, k+1, x);
//             }
//         }
//     }
// }

// vector<vector<string>> solveNQueens(int n) {
//     vector<vector<string>> r;
//     // vector<vector<bool>> board(n, vector<bool>(n, false));
//     // nQueen(board, 0, 0, 4, 0, "");
//     vector<int> cols(n, 0);
//     nQueen(n, 0, cols);
//     return r;
// }

set<int> cols;     // holds used columns
set<int> posDiag; // (r + c)
set<int> negDiag; // (r - c)
vector<vector<string>> res;

bool isSafe(int row, int col) {
    if(cols.find(col) == cols.end() &&
       posDiag.find(row + col) == posDiag.end() &&
       negDiag.find(row - col) == negDiag.end())
       return true;
    else
        return false;
}

int cnt {};
void backtracking(int n, int r, vector<vector<char>> &board) {
    if(n == r) {
        vector<string> solution;
        for(auto& row : board)
            solution.push_back(string(row.begin(), row.end()));

        res.push_back(solution);
        return;
    }

    for(int c = 0; c < n; ++c) {
        if(isSafe(r, c)) {
            cols.insert(c);
            posDiag.insert(r+c);
            negDiag.insert(r-c);
            board[r][c] = 'Q';

            backtracking(n, r+1, board);

            cols.erase(c);
            posDiag.erase(r+c);
            negDiag.erase(r-c);
            board[r][c] = '.';
        }
    }
}

vector<vector<string>> solveNQueens(int n) {
    vector<vector<char>> board(n, vector<char>(n, '.'));
    backtracking(n, 0, board);

    return res;
}

int main(int argc, char *argv[])
{
    int n = 4;
    if(argc > 1) {
        n = stoi(argv[1]);
    }

    auto res = solveNQueens(n);


    for(const auto& v : res) {
        cout << ++cnt << ". Solution: \n";
        for(const auto& e : v) {
            cout << e  << endl;
        }
        cout << endl;
    }
}

// Unresolved external symbol printf refereenced in function